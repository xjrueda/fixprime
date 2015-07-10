/* 
 * File:   Node.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 27, 2014, 9:57 PM
 */

#include "Node.h"
#include "Protocol.h"
#include "Component.h"

namespace fprime {

    Node::Node() : position(0) {
    }

    Node::Node(NodeType t) : _type(t), isRequired(false), position(0) {
    }

    Node::Node(const Node& other) :
    _type(other._type),
    value(other.value),
    position(other.position),
    isRequired(other.isRequired),
    field(other.field),
    protocolPtr(other.protocolPtr),
    componentPtr(other.componentPtr) {
        //childsByPosition.insert(other.childsByPosition.begin(), other.childsByPosition.end());
        childsByFieldId.insert(other.childsByFieldId.begin(), other.childsByFieldId.end());
        //cout << "Copy constructor for node fired" << endl;
    }

    Node::~Node() {
    }


    // Getters

    fprime::Field::FieldPtr Node::getField() {
        if (field == nullptr)
            throw runtime_error("No field setted for the node");
        return field;
    }
    //

    string Node::getValue() {
        return value->get();
    }
    //

    Node::NodeType Node::getType() {
        return _type;
    }


    //    // Setters

    void Node::setType(NodeType nodeType) {
        _type = nodeType;
    }

    void Node::setField(fprime::Field::FieldPtr fld) {
        try {
            if (fld == nullptr)
                throw runtime_error("Invalid field assigment to node.");
            fprime::DataHolderFactory factory;
            value = factory.create(fld->getDataType());

            if (_type == GROUP_INSTANCE) {
                throw runtime_error("The method is not available for groups instances.");
            }

            if (_type == ROOT_NODE) {
                throw runtime_error("The method is not available for root nodes.");
            }

            if (_type == REPEATING_GROUP) {
                value->set("0");
            }
            field = fld;
        } catch (exception& e) {
            throw runtime_error("at Node.setType: " + string(e.what()));
        }
    }

    void Node::setValue(string val) {
        //        if (_type == REPEATING_GROUP)
        //            throw runtime_error("Repeating group values are calculated");
        value->set(val);
    }

    void Node::setRequired(bool reqFlag) {
        isRequired = reqFlag;
    }

    void Node::setProtocol(fprime::Protocol* prot) {
        protocolPtr = prot;
    }

    void Node::setComponent(fprime::Component::ComponentPtr compPtr) {
        componentPtr = compPtr;
    }

    //    //Group operations

    void Node::appendChild(fprime::Node node) {
        if (!nestingRule(_type, node.getType())) {
            throw InvalidNodeNesting(decodeNodeType(_type), decodeNodeType(node.getType()));
        }
        position++;
        
        if (node.getType() == fprime::Node::GROUP_INSTANCE) {          
            unsigned int instanceId = (this->childsByFieldId.size()) + 1;
            this->childsByFieldId[instanceId] = node;
        }
        
        if ((node.getType() == fprime::Node::REPEATING_GROUP) || (node.getType() == fprime::Node::FIELD_NODE))
            this->childsByFieldId[node.field->getId()] = node;

//        this->childsByPosition[position] = node;
    }

    fprime::Node& Node::appendGroupInstance() {
        if (_type != Node::NodeType::REPEATING_GROUP) {
            throw std::runtime_error("appendGroupInstance is only allowed for BlockRepeating.");
        } else {
            Node newInstance(Node::NodeType::GROUP_INSTANCE);
            newInstance.resolveComponent(this->componentPtr);
            this->appendChild(newInstance);
        }
    }
    //operators

    fprime::Node& Node::operator()(unsigned int fieldId) {
        if (_type == Node::NodeType::REPEATING_GROUP) {
            throw runtime_error("The operator () is not available for repeating groups. Use []");
        }
        NodeMap::iterator search = childsByFieldId.find(fieldId);

        if (search != childsByFieldId.end()) {
            return search->second;
        } else {
            stringstream msg;
            msg << "at Node.operator(): Node for field " << fieldId << " does not exists";
            throw InvalidField(msg.str());
        }

    }

    fprime::Node& Node::operator[](unsigned int instanceIndex) {
        if (_type != Node::NodeType::REPEATING_GROUP) {
            throw runtime_error("The operator[] is only available for repeating groups.");
        }

        NodeMap::iterator search = childsByFieldId.find(instanceIndex);
        if (search != childsByFieldId.end())
            return search->second;
        else
            throw runtime_error("at Node.operator[] : Invalid repeating group instance");
    }

    void Node::stringify(string& outputString) {
        try {
            switch (_type) {
                case ROOT_NODE:
                case GROUP_INSTANCE:
                case REPEATING_GROUP:
                {
                    if (_type == REPEATING_GROUP) {
                        unsigned int id = this->getField()->getId();
                        this->addValuePair(outputString, id, this->getValue());
                    }
                    for (NodeMap::iterator it = childsByFieldId.begin(); it != childsByFieldId.end(); it++) {
                        it->second.stringify(outputString);
                    }
                    break;
                }
                case FIELD_NODE:
                {
                    unsigned int id = this->getField()->getId();
                    this->addValuePair(outputString, id, this->getValue());
                    break;
                }
            }
        } catch (exception& e) {
            cout << "at Node.stringify : " << e.what() << endl;
        }
    }

    void Node::addValuePair(string &s, unsigned int fieldId, string val) {
        try {
            if (!val.empty()) {
                if (!s.empty())
                    s += '\001';
                s = s + boost::lexical_cast<string>(fieldId) + string("=") + boost::lexical_cast<string>(val);
            }
        } catch (exception& e) {
            cout << "exception at Node.addValuePair : " << e.what();
        }
    }

    bool Node::nestingRule(NodeType parentType, NodeType nestedType) {
        bool result = false;
        switch (parentType) {
            case ROOT_NODE:
            case GROUP_INSTANCE:
            {
                if (nestedType == ROOT_NODE || nestedType == GROUP_INSTANCE)
                    result = false;
                else
                    result = true;
                break;
            }
            case FIELD_NODE:
            {
                result = false;
                break;
            }
            case REPEATING_GROUP:
            {
                if (nestedType != GROUP_INSTANCE)
                    result = false;
                else
                    result = true;
                break;
            }
        }
        return result;
    }

    string Node::decodeNodeType(NodeType t) {
        string typeStr;
        switch (t) {

            case ROOT_NODE:
            {
                typeStr = "ROOT_NODE";
                break;
            }
            case GROUP_INSTANCE:
            {
                typeStr = "GROUP_INSTANCE";
                break;
            }
            case FIELD_NODE:
            {
                typeStr = "FIELD_NODE";
                break;
            }
            case REPEATING_GROUP:
            {
                typeStr = "REPEATING_GROUP";
                break;
            }
            default:
            {
                typeStr = "INVALID";
                break;
            }
        }
        return typeStr;
    }

    void Node::resolveComponent(fprime::Component::ComponentPtr componentPtr) {
        // process fields
        vector<fprime::Component::FieldT> fields = componentPtr->getFields();
        vector<fprime::Component::FieldT>::iterator iter;
        for (iter = fields.begin(); iter < fields.end(); iter++) {
            fprime::Component::FieldT fieldt = *iter;
            string fieldType = fieldt.field->getDataType();
            fprime::Node child;
            if (fieldType == "NumInGroup") {
                cout << "Repeating field NumInGroup " << fieldt.field->getId() << endl;
                child.setType(fprime::Node::REPEATING_GROUP);
                if (this->componentPtr == nullptr)
                    throw runtime_error("at Node.resolveComponent: Component for repeating group " + fieldt.field->getName() + " was not found.");
                else {
                    fprime::Field::FieldPtr ctrlFieldPtr = this->componentPtr->getControlField();
                    child.setField(ctrlFieldPtr);
                }
                //                cout << "Repeating control field resolved " << child.getField()->getId() << endl;
            } else {
                child.setType(fprime::Node::FIELD_NODE);
                child.setField(fieldt.field);
            };

            child.setRequired(fieldt.isRequired);
            child.setProtocol(protocolPtr);
            appendChild(child);

        }

        // process components

        vector<fprime::Component::ComponentPtr> nestedComponents = componentPtr->getNestedComponents();
        vector<fprime::Component::ComponentPtr>::iterator cmpIter;
        for (cmpIter = nestedComponents.begin(); cmpIter < nestedComponents.end(); cmpIter++) {
            fprime::Component::ComponentPtr nestedComponent = *cmpIter;
            resolveComponent(nestedComponent);
        }


    }
}