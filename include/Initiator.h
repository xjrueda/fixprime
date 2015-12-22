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

#ifndef INITIATOR_H
#define	INITIATOR_H

#include "FixSessionSetup.h"
#include "SocketConnector.h"
#include "SocketException.h"
#include "Session.h"
#include <iostream>

using namespace std;

namespace fprime {

    class Initiator : public Session {
    public:
        Initiator();
        Initiator(FixSessionSetup);
        //        Initiator(const Initiator& orig);
        virtual ~Initiator();
        bool start();
    private:

        void startInitiator() {
            try {
                if (protocolPtr == nullptr)
                    throw runtime_error("Protocol not defined for  session.");
                if (callbacksManager == nullptr)
                    throw runtime_error("CallbacksManager not defined for  session.");

                SocketPtr socketPtr(new SocketConnector(sessionSetup.getHost(), sessionSetup.getPort()));
                setConnected(true);
                setSessionRunning(true);
                socketHandler(socketPtr);
            } catch (SocketException& se) {
                //TODO: log error
                cout << "Error trying to connect to server: " << se.description() << endl;
            } catch (exception& e) {
                //TODO: log error
                cout << "Error starting initiator: " << e.what() << endl;
            }
            this->stop();
        }
    };
}

#endif	/* INITIATOR_H */

