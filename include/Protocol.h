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

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <cstdlib>
#include "Node.h"
#include "Message.h"
#include "FixLoader.h"
#include "Field.h"
#include "Component.h"

using namespace std;

namespace fprime {
    class Protocol {
    public:
        typedef shared_ptr<Protocol> ProtocolPtr;
        Protocol();
        virtual ~Protocol();
        void addField(fprime::Field::FieldPtr);
        void addComponent(fprime::Component::ComponentPtr);
        fprime::Field::FieldPtr getField(unsigned int);
        void load();

        void setVersion(const string);
        void setSpecification(Json::Value);
        string getVersion();
        fprime::Message getMessage(string);
        fprime::Component::ComponentPtr getComponent(string);
        Json::Value& getSpecification();
        void populateNode(fprime::Node::NodePtr, Json::Value, bool);
    private:
        string version;
        Json::Value protocolSpec;
        ProtocolPtr protocolPtr;
        map<unsigned int, fprime::Field::FieldPtr > fields;
        map<string,string> dataTypes;
        map<const string, fprime::Message> messages;
        map<string,fprime::Component::ComponentPtr> components; 
        void loadFields();
        void loadComponents();
        void loadMessages();
        
//        void populateNode(FIXDF::Node&, Json::Value, bool);

    };
}

#endif	/* PROTOCOL_H */

