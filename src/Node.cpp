/* 
 * File:   Node.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 27, 2014, 9:57 PM
 */

#include "Node.h"
#include "Protocol.h"
#include "Component.h"

namespace hfe {

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
    childsByPosition(other.childsByPosition),
    childsByFieldId(other.childsByFieldId),
    protocolPtr(other.protocolPtr),
    componentPtr(other.componentPtr) {
    }

    Node::~Node() {
    }


    // Getters

    hfe::Field::FieldPtr Node::getField() {
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

    void Node::setField(hfe::Field::FieldPtr fld) {
        try {
            if (fld == nullptr)
                throw runtime_error("Invalid field assigment to node.");
            hfe::DataHolderFactory factory;
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
        if (_type == REPEATING_GROUP)
            throw runtime_error("Repeating group values are calculated");
        value->set(val);
    }

    void Node::setRequired(bool reqFlag) {
        isRequired = reqFlag;
    }

    void Node::setProtocol(hfe::Protocol* prot) {
        protocolPtr = prot;
    }

    void Node::setComponent(hfe::Component::ComponentPtr compPtr) {
        componentPtr = compPtr;
    }

    //    //Group operations

    void Node::appendChild(hfe::Node node) {
        if (!nestingRule(_type, node.getType())) {
            throw InvalidNodeNesting(decodeNodeType(_type), decodeNodeType(node.getType()));
        }
        position++;
        if ((node.getType() == hfe::Node::REPEATING_GROUP) || (node.getType() == hfe::Node::FIELD_NODE))
            this->childsByFieldId[node.field->getId()] = node;

        this->childsByPosition[position] = node;
    }

    hfe::Node& Node::appendGroupInstance() {
        if (_type != Node::NodeType::REPEATING_GROUP)
            throw std::runtime_error("appendGroupInstance is only allowed for BlockRepeating.");
        else {
            Node newInstance(Node::NodeType::GROUP_INSTANCE);
            newInstance.resolveComponent(this->componentPtr);
            appendChild(newInstance);
            //TODO:  control field increment
        }
    }
    //operators

    hfe::Node& Node::operator()(unsigned int fieldId) {
        if (_type == Node::NodeType::REPEATING_GROUP) {
            throw runtime_error("The operator () is not available for repeating groups. Use []");
        }

        //        return childsByFieldId[fieldId];

        NodeMap::iterator search = childsByFieldId.find(fieldId);


        if (search != childsByFieldId.end()) {
            return search->second;
        } else {
            stringstream msg;
            msg << "Node for field " << fieldId << " does not exists";
            throw runtime_error(msg.str());
        }

    }

    hfe::Node& Node::operator[](unsigned int instanceIndex) {
        if (_type != Node::NodeType::REPEATING_GROUP) {
            throw runtime_error("The operator[] is only available for repeating groups.");
        }

        NodeMap::iterator search = childsByPosition.find(instanceIndex);
        if (search != childsByPosition.end())
            return search->second;
        else
            throw runtime_error("Invalid repeating group instance");
    }
    //
    //    void Node::stringify(string &outputString, string separator, unsigned int indexValue) {
    //        try {
    //            //            switch (_type) {
    //            //                case ROOT_NODE:
    //            //                {
    //            //                    NodeMap childs = getChildsbyPosition();
    //            //                    for (NodeMap::iterator it = childs.begin(); it != childs.end(); it++) {
    //            //                        it->second->stringify(outputString, separator, indexValue);
    //            //                    }
    //            //                    break;
    //            //                }
    //            //                case FIELD_NODE:
    //            //                {
    //            //                    unsigned int id = this->getField()->getId();
    //            //                    this->addValuePair(outputString, separator, id, this->getValue(indexValue).toString());
    //            //                    break;
    //            //                }
    //            //                case REPEATING_GROUP:
    //            //                {
    //            //                    this->addValuePair(outputString, separator, this->getField()->getId(), this->getValue(indexValue).toString());
    //            //                    NodeMap childs = getChildsbyPosition();
    //            //                    for (int repetition = 0; repetition < values[indexValue].toInt(); repetition++) {
    //            //                        cout << "Repetition : " << repetition << endl;
    //            //                        for (NodeMap::iterator it = childs.begin(); it != childs.end(); it++) {
    //            //                            cout << "child  rep : " << repetition << endl;
    //            //                            Node::NodePtr node = it->second;
    //            //                            node->stringify(outputString, separator, repetition);
    //            //                        }
    //            //                    }
    //            //                    break;
    //            //                }
    //            //            }
    //        } catch (exception& e) {
    //            cout << "Error stringifying : " << e.what() << endl;
    //        }
    //    }
    //
    //    void Node::addValuePair(string &s, string separator, unsigned int fieldId, string val) {
    //        try {
    //            if (!val.empty()) {
    //                if (!s.empty())
    //                    s += separator;
    //                s = s + boost::lexical_cast<string>(fieldId) + string("=") + boost::lexical_cast<string>(val);
    //            }
    //        } catch (exception& e) {
    //            cout << "exception at addValuePair : " << e.what();
    //        }
    //    }
    //

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

    void Node::resolveComponent(hfe::Component::ComponentPtr componentPtr) {
        // process fields
        vector<hfe::Component::FieldT> fields = componentPtr->getFields();
        vector<hfe::Component::FieldT>::iterator iter;
        for (iter = fields.begin(); iter < fields.end(); iter++) {
            hfe::Component::FieldT fieldt = *iter;
            string fieldType = fieldt.field->getDataType();
            hfe::Node child;
            if (fieldType == "NumInGroup") {
                cout << "Repeating field NumInGroup " << fieldt.field->getId() << endl;
                child.setType(hfe::Node::REPEATING_GROUP);
                if (this->componentPtr == nullptr)
                    throw runtime_error("at Node.resolveComponent: Component for repeating group " + fieldt.field->getName() + " was not found.");
                else {
                    hfe::Field::FieldPtr ctrlFieldPtr = this->componentPtr->getControlField();
                    child.setField(ctrlFieldPtr);
                }
                //                cout << "Repeating control field resolved " << child.getField()->getId() << endl;
            } else {
                child.setType(hfe::Node::FIELD_NODE);
                child.setField(fieldt.field);
                cout << "field added " << child.getField()->getId() << endl;
            };

            child.setRequired(fieldt.isRequired);
            child.setProtocol(protocolPtr);
            appendChild(child);

        }

        // process components

        vector<hfe::Component::ComponentPtr> nestedComponents = componentPtr->getNestedComponents();
        cout << "Nested componentes = " << nestedComponents.size() << endl;
        vector<hfe::Component::ComponentPtr>::iterator cmpIter;
        for (cmpIter = nestedComponents.begin(); cmpIter < nestedComponents.end(); cmpIter++) {
            hfe::Component::ComponentPtr nestedComponent = *cmpIter;
            cout << "Nested componente is " << nestedComponent->getName() << endl;
            resolveComponent(nestedComponent);
        }


    }
}