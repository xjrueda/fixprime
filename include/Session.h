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

#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include "Socket.h"
#include "FixParser.h"
#include "Protocol.h"
#include "Message.h"
#include "FixSessionSetup.h"
#include "SocketException.h"
#include "FixParserExceptions.h"
#include <thread>
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <boost/lexical_cast.hpp>
#include  "SocketConnector.h"
#include "CallbacksManager.h"

namespace fprime {

    class Session {
    public:

        Session() {
        };

        Session(FixSessionSetup) {
        };

        ~Session() {
        };

        virtual bool start() = 0;

        virtual void stop() {
            setConnected(false);
            setIbRunning(false);
            setObRunning(false);
            setSessionRunning(false);
        }

        virtual void disconnect() {
            setConnected(false);
            setIbRunning(false);
            setObRunning(false);
            inboundCondition.notify_one();
            outboundCondition.notify_one();
        }

        virtual bool send(string msg) {
            if (!connected)
                //TODO: register log entry
                return false;
            else {
                pushOutbound(msg);
                return true;
            };
        }

        void setProtocol(fprime::Protocol::ProtocolPtr protPtr) {
            protocolPtr = protPtr;
        }

        virtual void setCallbacksManager(CallbacksManager::CallbacksManagerPtr cbm) {
            callbacksManager = cbm;
        }
    protected:
        fprime::Protocol::ProtocolPtr protocolPtr;
        typedef shared_ptr<SocketConnector> SocketPtr;
        CallbacksManager::CallbacksManagerPtr callbacksManager;
        FixSessionSetup sessionSetup;
        bool sessionRunning;
        bool ibpRunning;
        bool obpRunning;
        bool connected;
        mutex inboundLock;
        condition_variable inboundCondition;
        condition_variable outboundCondition;
        queue<string> outboundQueue;
        mutex outboundLock;
        string strBuffer;

        queue<string> inboundQueue;

        void inboundProcessor() {
            try {
                setIbRunning(true);
                fprime::FixParser parser;
                parser.setProtocol(protocolPtr);
                parser.setSeparator('\001');
                while (ibpRunning) {
                    unique_lock<mutex> lock(inboundLock);
                    while (inboundQueue.empty() && ibpRunning) {
                        inboundCondition.wait(lock);
                    }

                    if (ibpRunning) {
                        string rawMsg = inboundQueue.front();
                        inboundQueue.pop();
                        lock.unlock();
                        try {

                            fprime::FixParser::FlatMessage flatMessage = parser.explode(rawMsg);
                            if (flatMessage.orderedMap[0].value != protocolPtr->getVersion())
                                throw runtime_error("Invalid Message");
                            fprime::Message fixMsg = parser.parseMessage(flatMessage);
                            string callbackKey = fixMsg.getHeader()->getChild(8)->getValue() + "-" + fixMsg.getHeader()->getChild(35)->getValue();
                            callbacksManager->executeCallback(callbackKey, fixMsg, this);

                        } catch (exception& e) {
                            cout << "error in inboundprocessor " + string(e.what()) << " in message " << rawMsg << endl;
                            //TODO log error
                        }
                    }
                }
            } catch (exception& ex) {
                // TODO: log error
                cout << "General exception in inboundprocessor " + string(ex.what()) << endl;
                this->stop();
            }
            cout << "Inbound processor stopped" << endl;
            cout.flush();
        }

        void socketHandler(SocketPtr socketPtr) {
            thread t1(std::bind(&Session::inboundProcessor, this));
            t1.detach();

            thread t2(std::bind(&Session::outboundProcessor, this, socketPtr));
            t2.detach();
            setSessionRunning(true);
            while (connected) {
                std::string data;
                try {
                    *socketPtr >> data;
                    addToBuffer(data);
                    string msg;
                    while (getRawFixMessage(msg) && data.length() > 0) {
                        pushInbound(msg);
                        msg.clear();
                    }
                } catch (SocketException&) {
                    // TODO log error
                    setConnected(false);

                }
            }
        }

        void outboundProcessor(SocketPtr socketPtr) {
            setObRunning(true);
            while (obpRunning) {
                unique_lock<mutex> lock(outboundLock);
                while (outboundQueue.empty() && obpRunning) {
                    outboundCondition.wait(lock);
                }
                if (obpRunning) {
                    string rawMsg = outboundQueue.front();
                    outboundQueue.pop();
                    lock.unlock();
                    try {
                        *socketPtr << rawMsg;
                    } catch (SocketException& se) {
                        cout << "Error trying to send: " << se.description() << endl;
                        cout.flush();
                    }

                }
            }
        }

        void pushInbound(string rawMsg) {
            unique_lock<mutex> lock(inboundLock);
            inboundQueue.push(rawMsg);
            lock.unlock();
            inboundCondition.notify_one();
        }

        void pushOutbound(string rawMsg) {
            unique_lock<mutex> lock(outboundLock);
            outboundQueue.push(rawMsg);
            lock.unlock();
            outboundCondition.notify_one();
        }

        void setConnected(bool val) {
            mutex lock;
            lock.lock();
            connected = val;
            lock.unlock();
        }

        void setSessionRunning(bool val) {
            mutex lock;
            lock.lock();
            sessionRunning = val;
            lock.unlock();
        }

        void setIbRunning(bool val) {
            //            mutex lock;
            //            lock.lock();
            ibpRunning = val;
            //            lock.unlock();
        }

        void setObRunning(bool val) {
            //            mutex lock;
            //            lock.lock();
            obpRunning = val;
            //            lock.unlock();
        }

        void addToBuffer(const string& data) {
            strBuffer.append(data);
        }

        void addToBuffer(const char* data, size_t len) {
            strBuffer.append(data, len);
        }

        void clearBuffer() {
            strBuffer.clear();
        }

        bool getLength(int& length, std::string::size_type& pos,
                const std::string& buffer) throw ( RawMessageException) {
            if (!buffer.size()) return false;

            std::string::size_type startPos = buffer.find("\0019=", 0);
            if (startPos == std::string::npos) return false;
            startPos += 3;
            std::string::size_type endPos = buffer.find("\001", startPos);
            if (endPos == std::string::npos) return false;

            std::string strLength(buffer, startPos, endPos - startPos);

            try {
                length = boost::lexical_cast<int>(strLength);
                if (length < 0) throw RawMessageException();
            } catch (exception&) {
                throw RawMessageException();
            }

            pos = endPos + 1;
            return true;
        }

        bool getRawFixMessage(std::string& str) throw (RawMessageException) {
            std::string::size_type pos = 0;

            if (strBuffer.length() < 2) return false;
            pos = strBuffer.find("8=FIX");
            if (pos == std::string::npos) return false;
            strBuffer.erase(0, pos);

            int length = 0;

            try {
                if (getLength(length, pos, strBuffer)) {
                    pos += length;
                    if (strBuffer.size() < pos)
                        return false;

                    pos = strBuffer.find("\00110=", pos - 1);
                    if (pos == std::string::npos) return false;
                    pos += 4;
                    pos = strBuffer.find("\001", pos);
                    if (pos == std::string::npos) return false;
                    pos += 1;

                    str.assign(strBuffer, 0, pos);
                    strBuffer.erase(0, pos);
                    return true;
                }
            } catch (RawMessageException& e) {
                if (length > 0)
                    strBuffer.erase(0, pos + length);
                else
                    strBuffer.erase();

                throw e;
            }

            return false;
        }
    };
}
#endif /* SESSION_H */