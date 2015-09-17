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

    Node::Node() {
    }

    Node::Node(NodeType t) : _type(t), isRequired(false) {
    }

    Node::Node(const Node& other) :
    _type(other._type),
    isRequired(other.isRequired),
    field(other.field),
    protocolPtr(other.protocolPtr),
    componentPtr(other.componentPtr) {

        if (other._type == fprime::Node::NodeType::FIELD_NODE || other._type == fprime::Node::NodeType::REPEATING_GROUP) {
            fprime::DataHolderFactory factory;
            this->value = factory.create(other.field->getDataType());
            const string val = other.value->get();
            this->value->set(val);
        }

        childsVector.clear();
        childsByFieldId.clear();
        for (NodeVector::const_iterator itr = other.childsVector.begin(); itr != other.childsVector.end(); itr++) {
            NodePtr newNode(new Node(**itr));
            childsVector.push_back(newNode);
            if(other._type == fprime::Node::NodeType::ROOT_NODE || other._type == fprime::Node::NodeType::GROUP_INSTANCE)
                childsByFieldId[newNode->getField()->getId()] = newNode;
            
            if(other._type == fprime::Node::NodeType::REPEATING_GROUP)
                childsByFieldId[childsVector.size()] = newNode;
        }
        
//        if (_type != fprime::Node::NodeType::ROOT_NODE)
//            cout << "Node " << field->getId() << " copied" << endl;
//        else
//            cout << "Root Node " << " copied" << endl;
            
    }

    Node::~Node() {
    }

    fprime::Node& Node::operator=(const fprime::Node& other) {
        _type = other._type;
        value = other.value;
        isRequired = other.isRequired;
        field = other.field;
        protocolPtr = other.protocolPtr;
        componentPtr = other.componentPtr;

        fprime::DataHolderFactory factory;

        if (other._type == fprime::Node::NodeType::FIELD_NODE) {
            fprime::DataHolderFactory factory;
            value = factory.create(other.field->getDataType());
            this->value = factory.create(other.field->getDataType());
            const string val = other.value->get();
            this->value->set(val);
        }

        childsVector.clear();
        childsByFieldId.clear();
        
        for (NodeVector::const_iterator itr = other.childsVector.begin(); itr != other.childsVector.end(); itr++) {
            NodePtr newNode(new Node(**itr));
            childsVector.push_back(newNode);
            if(other._type == fprime::Node::NodeType::ROOT_NODE || other._type == fprime::Node::NodeType::GROUP_INSTANCE)
                childsByFieldId[newNode->getField()->getId()] = newNode;
            
            if(other._type == fprime::Node::NodeType::REPEATING_GROUP)
                childsByFieldId[childsVector.size()] = newNode;
        }
        return *this;
    }


    // Getters

    fprime::Field::FieldPtr Node::getField() {
        if (field == nullptr)
            throw runtime_error("No field setted for the node");
        return field;
    }
    //

    const string Node::getValue() {
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
                stringstream ss;
                ss << "This method is not available for root nodes. setting field " << fld->getId();
                throw runtime_error(ss.str());
            }

//            if (_type == REPEATING_GROUP) {
//                value->set("0");
//            }
            field = fld;
        } catch (exception& e) {
            throw runtime_error("at Node.setField: " + string(e.what()));
        }
    }

    void Node::setValue(string val) {
        if (_type == REPEATING_GROUP)
            throw runtime_error("Repeating group values are calculated");
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

    void Node::appendChild(fprime::Node::NodePtr nodePtr) {

        if (!nestingRule(_type, nodePtr->getType())) {
            throw InvalidNodeNesting(decodeNodeType(_type), decodeNodeType(nodePtr->getType()));
        }

        if (nodePtr->getType() == fprime::Node::GROUP_INSTANCE) {
            unsigned int instanceId = (this->childsByFieldId.size()) + 1;
            childsByFieldId[instanceId] = nodePtr;
        }

        if ((nodePtr->getType() == fprime::Node::REPEATING_GROUP) || (nodePtr->getType() == fprime::Node::FIELD_NODE)) {
            childsByFieldId[nodePtr->field->getId()] = nodePtr;
        }
        childsVector.push_back(nodePtr);
    }

    void Node::appendGroupInstance() {
        if (_type != Node::NodeType::REPEATING_GROUP) {
            throw std::runtime_error("appendGroupInstance is only allowed for BlockRepeating.");
        } else {
            Node::NodePtr newInstance(new Node(Node::NodeType::GROUP_INSTANCE));
            newInstance->resolveComponent(this->componentPtr);
            this->appendChild(newInstance);
            this->value->set(boost::lexical_cast<string>(childsByFieldId.size()));
        }
    }
    //operators

    fprime::Node::NodePtr Node::getChild(unsigned int fieldId) {
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

    fprime::Node::NodePtr Node::getInstance(unsigned int instanceIndex) {
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
                    for (int i = 0; i < childsVector.size(); i++) {
                        childsVector[i]->stringify(outputString);
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
                    s += ";";
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
            fprime::Node::NodePtr child(new Node());
            //            if (fieldType == "NUMINGROUP") {
            //                child.setType(fprime::Node::REPEATING_GROUP);
            //                if (this->componentPtr == nullptr)
            //                    throw runtime_error("at Node.resolveComponent: Component for repeating group " + fieldt.field->getName() + " was not found.");
            //                else {
            //                    fprime::Field::FieldPtr ctrlFieldPtr = this->componentPtr->getControlField();
            //                    child.setField(ctrlFieldPtr);
            //                }
            //                //                cout << "Repeating control field resolved " << child.getField()->getId() << endl;
            //            } else {
            //
            //            };
            child->setType(fprime::Node::FIELD_NODE);
            child->setField(fieldt.field);

            child->setRequired(fieldt.isRequired);
            child->setProtocol(protocolPtr);
            appendChild(child);

        }

        // process components

        vector<fprime::Component::ComponentPtr> nestedComponents = componentPtr->getNestedComponents();
        vector<fprime::Component::ComponentPtr>::iterator cmpIter;
        for (cmpIter = nestedComponents.begin(); cmpIter < nestedComponents.end(); cmpIter++) {
            fprime::Component::ComponentPtr nestedComponent = *cmpIter;

            if (nestedComponent->getType() == "BlockRepeating") {

                fprime::Field::FieldPtr ctrlFieldPtr = nestedComponent->getControlField();
                fprime::Node::NodePtr child(new Node());
                child->setType(fprime::Node::REPEATING_GROUP);
                child->setField(ctrlFieldPtr);

                //TODO Define required
                child->setRequired(false);
                child->setProtocol(protocolPtr);
                child->setComponent(nestedComponent);
                appendChild(child);

            } else {
                resolveComponent(nestedComponent);
            }
        }


    }
}