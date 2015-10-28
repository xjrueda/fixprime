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

#include "FixSessionSetup.h"

namespace fprime {

    FixSessionSetup::FixSessionSetup() {
    };

    FixSessionSetup::~FixSessionSetup() {
    };

//    FixSessionSetup::FixSessionSetup(const FixSessionSetup& org) {
//    }

    //Setters

    void FixSessionSetup::setType(string t) {
        type_ = t;
    }

    void FixSessionSetup::setHost(string h) {
        host = h;
    }

    void FixSessionSetup::setPort(short p) {
        port = p;
    }

    void FixSessionSetup::setSender(string s) {
        sender = s;
    }

    void FixSessionSetup::setTarget(string trg) {
        target = trg;
    }

    void FixSessionSetup::setResetOnLogon(string rol) {
        resetOnLogon = rol;
    }

    void FixSessionSetup::setResetOnLogout(string rolout) {
        resetOnLogout = rolout;
    }

    void FixSessionSetup::setResetOnDisconnect(string rod) {
        resetOnDisconnect = rod;
    }

    void FixSessionSetup::setRefreshOnLogon(string rfol) {
        refreshOnLogon = rfol;
    }

    void FixSessionSetup::setProtocol(string prot) {
        protocol = prot;
    }

    void FixSessionSetup::setDefaultAppVersion(string dappv) {
        defaultAppVersion = dappv;
    }

    void FixSessionSetup::setHeartbeatInterval(string hbi) {
        heartbeatInterval = hbi;
    }

    void FixSessionSetup::setUser(string usr) {
        user = usr;
    }

    void FixSessionSetup::setPassword(string pwd) {
        password = pwd;
    }

    //Getters

    string FixSessionSetup::getType() {
        return type_;
    }

    string FixSessionSetup::getHost() {
        return host;
    }

    short FixSessionSetup::getPort() {
        return port;
    }

    string FixSessionSetup::getSender() {
        return sender;
    }

    string FixSessionSetup::getTarget() {
        return target;
    }

    string FixSessionSetup::getResetOnLogon() {
        return resetOnLogon;
    }

    string FixSessionSetup::getResetOnLogout() {
        return resetOnLogout;
    }

    string FixSessionSetup::getResetOnDisconnect() {
        return resetOnDisconnect;
    }

    string FixSessionSetup::getRefreshOnLogon() {
        return refreshOnLogon;
    }

    string FixSessionSetup::getProtocol() {
        return protocol;
    }

    string FixSessionSetup::getDefaultAppVersion() {
        return defaultAppVersion;
    }

    string FixSessionSetup::getHeartbeatInterval() {
        return heartbeatInterval;
    }

    string FixSessionSetup::getUser() {
        return user;
    }

    string FixSessionSetup::getPassword() {
        return password;
    }
}