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

namespace hfe {
    class Protocol {
    public:
        typedef shared_ptr<Protocol> ProtocolPtr;
        Protocol();
        virtual ~Protocol();
        void addField(hfe::Field::FieldPtr);
        void addComponent(hfe::Component::ComponentPtr);
        hfe::Field::FieldPtr getField(unsigned int);
        void load();

        void setVersion(const string);
        void setSpecification(Json::Value);
        string getVersion();
        hfe::Message getMessage(string);
        hfe::Component::ComponentPtr getComponent(string);
        Json::Value& getSpecification();
        void populateNode(hfe::Node&, Json::Value, bool);
    private:
        string version;
        Json::Value protocolSpec;
        ProtocolPtr protocolPtr;
        map<unsigned int, hfe::Field::FieldPtr > fields;
        map<string,string> dataTypes;
        map<const string, hfe::Message> messages;
        map<string,hfe::Component::ComponentPtr> components; 
        void loadFields();
        void loadComponents();
        void loadMessages();
        
//        void populateNode(FIXDF::Node&, Json::Value, bool);

    };
}

#endif	/* PROTOCOL_H */

