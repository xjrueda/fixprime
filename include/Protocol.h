/* 
 * File:   Protocol.h
 * Author: DeveloperPrime
 *
 * Created on September 29, 2014, 9:13 PM
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
        void populateNode(fprime::Node&, Json::Value, bool);
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

