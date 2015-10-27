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


#ifndef FIXSESSION_H
#define	FIXSESSION_H

#include <boost/asio.hpp>
#include "CallbacksManager.h"
#include "FixParserExceptions.h"
#include "FixParser.h"
#include "Message.h"
#include "Protocol.h"
#include <queue>
#include <thread>
#include <mutex>
#include "Acceptor.h"
#include "Socket.h"
#include "FixSessionSetup.h"



using boost::asio::ip::tcp;

namespace fprime {

    const int max_length = 10240;

    class FixSession {
    public:
        typedef shared_ptr<FixSession> FixSessionPtr;
        FixSession(FixSessionSetup);
        FixSession(const FixSession& orig);
        virtual ~FixSession();

        void inboundProcessor();
        void setCallbackManager(fprime::CallbacksManager::CallbacksManagerPtr);
        void setProtocol(fprime::Protocol::ProtocolPtr);
        bool startInboundProcessor();
        bool stopInboundProcessor();
        void stopAbortProcessor();
        bool connect();
        bool disconnect();
        void start(Socket::IOSPtr, unsigned short);
        void stop();
        void send(string);
    private:
        shared_ptr<fprime::Socket> connectorPtr;
        fprime::Protocol::ProtocolPtr protocolPtr;
        queue<fprime::Message> outboundQueue;
        Socket::MessageQueue inboundQueue;
        fprime::CallbacksManager::CallbacksManagerPtr callbacksManager;
        bool connected;
        bool ibpRunning;
        bool sessionRunning;
        condition_variable inboundCondition;
        mutex inboundLock;
        mutex connectionLock;
        mutex runningLock;
        string strBuffer;
        void setConnected(bool);
        void setSessionRunning(bool);
        void setIbRunning(bool);
        FixSessionSetup sessionSetup;
    };

}

#endif	/* FIXSESSION_H */

