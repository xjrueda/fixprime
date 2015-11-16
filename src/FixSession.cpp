/*
 * Copyright (c) 2015, Juan Carlos Rueda (xjrueda@gmail.com) All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the FixMate  Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL JUAN CARLOS RUEDA BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "FixSession.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Initiator.h"

namespace fprime {

    FixSession::FixSession(FixSessionSetup ssetup) : sessionSetup(ssetup), connected(false), ibpRunning(false) {
        cout << "Session Type :" <<  sessionSetup.getType() << endl;
        if (sessionSetup.getType() == "Acceptor") {
            connectorPtr.reset(new fprime::Acceptor);
        } else {
            connectorPtr.reset(new fprime::Initiator);
        }
    }

    FixSession::FixSession(const FixSession& orig) {
    }

    FixSession::~FixSession() {
        cout << "FixSession released" << endl;
    }

    void FixSession::inboundProcessor() {

        Socket::MessageQueuePtr inboundQueue = connectorPtr->getInboundQueuePtr();

        setIbRunning(true);
        fprime::FixParser parser;
        parser.setProtocol(protocolPtr);
        parser.setSeparator('\001');

        while (ibpRunning) {
            unique_lock<mutex> lock(connectorPtr->inboundLock);

            while (inboundQueue->empty()) {
                connectorPtr->inboundCondition.wait(lock);
            }
            string rawMsg = inboundQueue->front();
            inboundQueue->pop();
            lock.unlock();
            try {
                fprime::FixParser::FlatMessage flatMessage = parser.explode(rawMsg);
                fprime::Message fixMsg = parser.parseMessage(flatMessage);
                string callbackKey = fixMsg.getHeader()->getChild(8)->getValue() + "-" + fixMsg.getHeader()->getChild(35)->getValue();

                // delegates the method to it handler
                //cout << "Executing delegate" << endl;
                callbacksManager->executeCallback(callbackKey, fixMsg, this);

            } catch (exception& e) {
                cout << "error in inboundprocessor " + string(e.what()) << " in message " << rawMsg << endl;
                setIbRunning(false);
                //TODO log error
            }
            
        }

    }
    

    void FixSession::setCallbackManager(fprime::CallbacksManager::CallbacksManagerPtr cbMan) {
        callbacksManager = cbMan;
    }

    void FixSession::setProtocol(fprime::Protocol::ProtocolPtr protPtr) {
        protocolPtr = protPtr;
    }

    bool FixSession::startInboundProcessor() {
        try {
            // launch the processor for inbound messages
            thread t1(bind(&FixSession::inboundProcessor, this));
            t1.detach();
            return true;
        } catch (...) {
            return false;
        }
    }

    bool FixSession::stopInboundProcessor() {
        if (inboundQueue.empty()) {
            setIbRunning(false);
            return true;
        } else
            return false;
    }

    void FixSession::stopAbortProcessor() {
        connectorPtr->stop();
        setIbRunning(false);
    }

//    bool FixSession::connect() {
//        setConnected(true);
//    }
//
//    bool FixSession::disconnect() {
//        setConnected(false);
//    }

    void FixSession::start(Socket::IOSPtr iosPtr) {
        if (!startInboundProcessor())
            throw runtime_error("at FixSession.start : InboundProcessor could not be started.");


        setSessionRunning(true);
        if (sessionSetup.getType() == "Acceptor") {
            connectorPtr->start(iosPtr, sessionSetup.getPort());
            cout << "Acceptor started" << endl;
        } else {
            connectorPtr->start(iosPtr, sessionSetup.getHost(), sessionSetup.getPort());
            cout << "Initiator started" << endl;
        }
    }

    void FixSession::stop() {
        //disconnect();
        connectorPtr->stop();
        bool emtyqueue = false;
        while (!emtyqueue) {
            emtyqueue = stopInboundProcessor();
            usleep(500000);
        }

        cout << "Session Stopped" << endl;
    }

    void FixSession::send(string msg) {
        
//        connectorPtr->pushOutbound(msg);
        
        if (!connectorPtr->send(msg)) {
            //TODO Write to log
        }
    }

    void FixSession::setConnected(bool val) {
        mutex lock;
        lock.lock();
        connected = val;
        lock.unlock();
    }

    void FixSession::setSessionRunning(bool val) {
        mutex lock;
        lock.lock();
        sessionRunning = val;
        lock.unlock();
    }

    void FixSession::setIbRunning(bool val) {
        mutex lock;
        lock.lock();
        ibpRunning = val;
        lock.unlock();
    }


}