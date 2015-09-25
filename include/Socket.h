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

#ifndef SOCKET_H
#define	SOCKET_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "FixParserExceptions.h"

using namespace boost::asio;
using namespace std;

namespace fprime {

    const int recBuffSize = 10240;
    
    class Socket {
    public:

        Socket() {
        };

        virtual ~Socket() {
        }

        typedef boost::shared_ptr<ip::tcp::socket> SocketPtr;

        struct RawMessage {

            RawMessage(const string txt) : rawMsg(txt) {
            }

            ~RawMessage() {
            }

            void setText(const string txt) {
                rawMsg = txt;
            }

            string getText() {
                return rawMsg;
            }

            string rawMsg;
        };

        typedef queue<string> MessageQueue;
        typedef shared_ptr<MessageQueue> MessageQueuePtr;

        virtual bool start(io_service& io_service, unsigned short port) = 0;
        //virtual bool start(io_service& io_service, string ip, unsigned short port) = 0;
        virtual void stop() = 0;
        virtual void close() = 0;
        virtual bool send() = 0;
        virtual bool receive() = 0;
        
        MessageQueuePtr getInboundQueuePtr() {
            return inboundQueuePtr;
        }
        
        condition_variable inboundCondition;
        mutex inboundLock;
    protected:
        MessageQueuePtr inboundQueuePtr;
        SocketPtr socketPtr;
        
        boost::asio::io_service service;

        bool started;
        bool connected;
        bool ibpRunning;
        bool sessionRunning;
        
        
        mutex connectionLock;
        string strBuffer;

        void pushInbound(const string msg) {
            unique_lock<mutex> lock(inboundLock);
            inboundQueuePtr->push(msg);
            lock.unlock();
            inboundCondition.notify_one();
        }

        void setConnected(bool val) {
            mutex lock;
            lock.lock();
            connected = val;
            lock.unlock();
        }

        void setStarted(bool val) {
            mutex lock;
            lock.lock();
            started = val;
            lock.unlock();
        }

        void setSessionRunning(bool val) {
            mutex lock;
            lock.lock();
            sessionRunning = val;
            lock.unlock();
        }

        void setIbRunning(bool val) {
            mutex lock;
            lock.lock();
            ibpRunning = val;
            lock.unlock();
        }
        
        bool dummy() {
            cout.flush();
            return true; 
        }

        void addToBuffer(const string& data) {
            strBuffer.append(data);
        }

        void addToBuffer(const char* data, size_t len) {
            strBuffer.append(data, len);
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
            pos = strBuffer.find("8=");
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

#endif	/* SOCKET_H */