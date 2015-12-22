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

#ifndef FIXSESSIONSETUP_H
#define FIXSESSIONSETUP_H

#include <string>
#include <iostream>

using namespace std;

namespace fprime {

    class FixSessionSetup {
    public:
        FixSessionSetup();
        virtual ~FixSessionSetup();
//        FixSessionSetup(const FixSessionSetup& org);
        //Setters
        void setType(string);
        void setHost(string);
        void setPort(short);
        void setSender(string);
        void setTarget(string);
        void setResetOnLogon(string);
        void setResetOnLogout(string);
        void setResetOnDisconnect(string);
        void setRefreshOnLogon(string);
        void setProtocol(string);
        void setDefaultAppVersion(string);
        void setHeartbeatInterval(string);
        void setUser(string);
        void setPassword(string);

        //Getters
        string getType();
        string getHost();
        int getPort();
        string getSender();
        string getTarget();
        string getResetOnLogon();
        string getResetOnLogout();
        string getResetOnDisconnect();
        string getRefreshOnLogon();
        string getProtocol();
        string getDefaultAppVersion();
        string getHeartbeatInterval();
        string getUser();
        string getPassword();

    private:
        string type_;
        string host;
        short port;
        string sender;
        string target;
        string resetOnLogon;
        string resetOnLogout;
        string resetOnDisconnect;
        string refreshOnLogon;
        string protocol;
        string defaultAppVersion;
        string heartbeatInterval;
        string user;
        string password;

    };

}

#endif /* FIXSESSIONSETUP_H */