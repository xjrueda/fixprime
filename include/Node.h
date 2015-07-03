/* 
 * File:   Node.h
 * Author: DeveloperPrime
 *
 * Created on September 27, 2014, 9:57 PM
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


namespace hfe {
    class Protocol;
    class Node {
    public:

        enum NodeType {
            ROOT_NODE,
            FIELD_NODE,
            REPEATING_GROUP,
            GROUP_INSTANCE
        };
        typedef map<unsigned int, hfe::Node> NodeMap;
        Node();
        Node(NodeType);
        Node(const Node& other);
        virtual ~Node();

        // Getters
        hfe::Field::FieldPtr getField();
        string getValue();
        NodeType getType();

        //Setters
        void setType(NodeType);


        void setField(hfe::Field::FieldPtr);
        void setValue(string);
        void setRequired(bool);
        void setProtocol(hfe::Protocol*);
        void setComponent(hfe::Component::ComponentPtr);

        //Group operations
        void appendChild(hfe::Node);
        hfe::Node& appendGroupInstance();
        void resolveComponent(hfe::Component::ComponentPtr);
        //operators

        hfe::Node& operator()(unsigned int);
        hfe::Node& operator[](unsigned int);

        // Utilities

        void stringify(string& outputString);
    private:
        NodeType _type;
        hfe::DataHolder::DataTypePtr value;
        unsigned int position;
        bool isRequired;

        hfe::Field::FieldPtr field;
//        NodeMap childsByPosition;
        NodeMap childsByFieldId;

        void addValuePair(string &ss, unsigned int fieldId, string val);
        bool nestingRule(NodeType, NodeType);

        
        string decodeNodeType(NodeType);
        Json::Value nodeSpec;
        Json::Value components;
        hfe::Protocol* protocolPtr;
        hfe::Component::ComponentPtr componentPtr;
        
    };
}
#endif	/* NODE_H */

