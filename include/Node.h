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
        typedef map<unsigned int, fprime::Node> NodeMap;
        Node();
        Node(NodeType);
        Node(const Node& other);
        virtual ~Node();

        // Getters
        fprime::Field::FieldPtr getField();
        string getValue();
        NodeType getType();

        //Setters
        void setType(NodeType);


        void setField(fprime::Field::FieldPtr);
        void setValue(string);
        void setRequired(bool);
        void setProtocol(fprime::Protocol*);
        void setComponent(fprime::Component::ComponentPtr);

        //Group operations
        void appendChild(fprime::Node);
        fprime::Node& appendGroupInstance();
        void resolveComponent(fprime::Component::ComponentPtr);
        //operators

        fprime::Node& operator()(unsigned int);
        fprime::Node& operator[](unsigned int);

        // Utilities

        void stringify(string& outputString);
    private:
        NodeType _type;
        fprime::DataHolder::DataTypePtr value;
        unsigned int position;
        bool isRequired;

        fprime::Field::FieldPtr field;
//        NodeMap childsByPosition;
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

