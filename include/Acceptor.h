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

#ifndef ACCEPTOR_H
#define	ACCEPTOR_H

#include "Socket.h"
#include <iostream>

using namespace boost::asio;
using namespace std;

namespace fprime {

    class Acceptor : public fprime::Socket {
    public:
        Acceptor();
        Acceptor(const Acceptor& orig);
        virtual ~Acceptor();
        bool start(Socket::IOSPtr, unsigned short);
        bool start(Socket::IOSPtr, string, unsigned short);
    private:

        void startAcceptor(IOSPtr ioService, unsigned short port) {
            try {
                ip::tcp::endpoint ep(ip::tcp::v4(), port);
                ip::tcp::acceptor acc(*ioService, ep);
                setStarted(true);
                setConnected(false);
                //cout << "acceptor started" << endl;
                while (started) {
                    if (!connected) {
                        socketPtr.reset(new ip::tcp::socket(*ioService));
                        acc.accept(*socketPtr);
                        setConnected(true);                      
                        clientConnection(socketPtr);
                    }
                    cout << "acceptor listening for new connection" << endl;
                }
            } catch (exception& e) {
                setStarted(false);
                setConnected(false);
                //TODO: register error in log
            }
        }

//        void clientConnection(SocketPtr sock) {
//            clearBuffer();
//            cout << "client session started" << endl;
//            while (connected) {
//                boost::system::error_code error;
//                char data[recBuffSize];
//                size_t length = sock->read_some(boost::asio::buffer(data), error);
//                if (error == boost::asio::error::eof) {
//                    cout << "Connection closed cleanly by peer" << endl;
//                    setConnected(false);
//                    break; // Connection closed cleanly by peer.
//                } else if (error) {
//                    setConnected(false);
//                    TODO: Register error in log
//                    throw boost::system::system_error(error); // Some other error.
//                }
//                stringstream ss;
//                ss << data;
//                addToBuffer(ss.str());
//                string msg;
//                while (getRawFixMessage(msg) && length > 0) {
//                    cout << "Pushing message in queue" << msg << endl;
//                    pushInbound(msg);
//
//                     Response 
//                    string response = "Procesed";
//                    size_t response_length = response.length();
//                    
//                    boost::asio::write(*sock, boost::asio::buffer(response, response_length));
//                    cout << "Responded" << endl;
//                    msg.clear();
//                }
//                cout << "Next" << endl;
//                cout.flush();
//            }
//            sock->close();
//            setConnected(false);
//            cout << "Messages in queue : " << inboundQueuePtr->size() << endl;
//            cout << "client session closed" << endl;
//        }

    };
}

#endif	/* ACCEPTOR_H */

