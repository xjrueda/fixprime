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

#ifndef NODE_H
#define	NODE_H

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>
#include <string>
#include "Field.h"
#include "FixParserExceptions.h"
#include "Value.h"
#include "Component.h"
#include "DataHolder.h"
#include "DataHolderFactory.h"


using namespace std;


namespace fprime {
    class Protocol;
    class Node {
    public:

        enum NodeType {
            ROOT_NODE,
            FIELD_NODE,
            REPEATING_GROUP,
            GROUP_INSTANCE
        };
        
        typedef shared_ptr<fprime::Node> NodePtr;
        typedef map<unsigned int, NodePtr> NodeMap;
        typedef vector<NodePtr> NodeVector;
        
        Node();
        Node(NodeType);
        Node(const Node& other);
        virtual ~Node();
        
        // Getters
        fprime::Field::FieldPtr getField();
        const string getValue();
        NodeType getType();

        //Setters
        void setType(NodeType);


        void setField(fprime::Field::FieldPtr);
        void setValue(string);
        void setRequired(bool);
        void setProtocol(fprime::Protocol*);
        void setComponent(fprime::Component::ComponentPtr);

        //Group operations
        void appendChild(fprime::Node::NodePtr);
        void appendGroupInstance();
        void resolveComponent(fprime::Component::ComponentPtr);
        fprime::Node::NodePtr getChild(unsigned int);
        fprime::Node::NodePtr getInstance(unsigned int);
        
        //operators
        fprime::Node&  operator=(const fprime::Node& other);

        // Utilities

        void stringify(string& outputString);
    private:
        NodeType _type;
        fprime::DataHolder::DataTypePtr value;
        bool isRequired;

        fprime::Field::FieldPtr field;
        NodeVector childsVector;
        NodeMap childsByFieldId;

        void addValuePair(string &ss, unsigned int fieldId, string val);
        bool nestingRule(NodeType, NodeType);

        
        string decodeNodeType(NodeType);
        Json::Value nodeSpec;
        Json::Value components;
        fprime::Protocol* protocolPtr;
        fprime::Component::ComponentPtr componentPtr;
        
    };
}
#endif	/* NODE_H */

