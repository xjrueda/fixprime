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

#include <thread>

#include "Initiator.h"
#include "Socket.h"

using namespace boost::asio;
using namespace std;

namespace fprime {

    Initiator::Initiator() {
        inboundQueuePtr.reset(new MessageQueue);
    }

    Initiator::Initiator(const Initiator& orig) {
    }

    Initiator::~Initiator() {
    }

    bool Initiator::start(Socket::IOSPtr iosPtr, string host, unsigned short port) {
        try {
            tcp::resolver resolver(*iosPtr);
            socketPtr.reset(new ip::tcp::socket(*iosPtr));
            stringstream ss;
            ss << port;
            boost::asio::connect(*socketPtr, resolver.resolve({host.c_str(), ss.str().c_str()}));
            setStarted(true);
            setConnected(true);
            thread t1(bind(&Initiator::clientConnection, this, socketPtr));
            t1.detach();
            return true;

            cout << "Initiator started" << endl;
        } catch (exception& e) {
            setStarted(false);
            setConnected(false);
            return false;
            //TODO: register error in log
        }
    }

    bool Initiator::start(Socket::IOSPtr iosPtr, unsigned short port) {
        return false;
    }

}