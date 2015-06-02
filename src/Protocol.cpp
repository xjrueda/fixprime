/* 
 * File:   Protocol.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:13 PM
 */

#include "Protocol.h"
#include "Component.h"

namespace hfe {

    Protocol::Protocol() {
    }

    Protocol::~Protocol() {
    }

    void Protocol::addField(hfe::Field::FieldPtr field) {
        fields[field->getId()] = field;
    }

    void Protocol::addComponent(hfe::Component::ComponentPtr component) {
        components[component->getName()] = component;
    }

    hfe::Component::ComponentPtr Protocol::getComponent(string compName) {
        auto search = components.find(compName);
        if (search == components.end())
            throw ComponentNotFound(compName);
        else
            return search->second;
    }

    hfe::Field::FieldPtr Protocol::getField(unsigned int id) {
        map<unsigned int, hfe::Field::FieldPtr >::iterator search;
        search = fields.find(id);
        if (search != fields.end())
            return search->second;
        else {
            stringstream msg;
            msg << "Field " << id << "does not exists in protocol " << version;
            throw runtime_error(msg.str());
        }
    }

    void Protocol::load() {
        loadFields();
        loadComponents();
        loadMessages();
    }

    void Protocol::loadFields() {
        try {
            if (protocolSpec["Fields"].empty()) {
                std::runtime_error("No fields specified for current  protocol ");

            } else {

                // Gets the fields members of the protocol
                std::vector<string> fieldCodes = protocolSpec["Fields"].getMemberNames();

                // process the fields
                for (std::vector<string>::iterator itr = fieldCodes.begin(); itr != fieldCodes.end(); itr++) {
                    try {
                        hfe::Field::FieldPtr field(new hfe::Field(boost::lexical_cast<unsigned int>(*itr)));
                        // completes the field properties
                        field->setName(protocolSpec["Fields"][*itr]["name"].asString());
                        field->setDataType(protocolSpec["Fields"][*itr]["dataType"].asString());

                        //Load valid values
                        try {
                            if (protocolSpec["Fields"][*itr]["validValues"].empty()) {
                                std::vector<string> validValues = protocolSpec["Fields"][*itr]["validValues"].getMemberNames();
                                for (std::vector<string>::iterator itValues = validValues.begin(); itValues != validValues.end(); itValues++) {
                                    field->addValidValue(string(*itValues), protocolSpec["Fields"][*itr]["validValues"][*itValues].asString());
                                }
                            }
                            addField(field);
                        } catch (exception& e) {
                            throw std::runtime_error("error loading valid values: " + string(e.what()));
                        }
                    } catch (exception e) {
                        throw std::runtime_error("Exception loading field " + *itr + ": " + e.what());
                    }
                }

            }
        } catch (exception& e) {
            throw std::runtime_error("at Protocol.loadField:" + string(e.what()));
        }
    }

    void Protocol::loadComponents() {
        try {
            if (protocolSpec["Components"].empty()) {
                throw std::runtime_error("No components specified for current  protocol ");
            } else {

                vector<pair < hfe::Component::ComponentPtr, string>> componentDependencies;
                std::vector<string> names = protocolSpec["Components"].getMemberNames();
                // Process the components
                for (std::vector<string>::iterator itr = names.begin(); itr != names.end(); itr++) {
                    //gets the component json Value
                    Json::Value componentSpec = protocolSpec["Components"][*itr];

                    //gets the component's properties
                    string componentType = componentSpec["type"].asString();

                    string componentName = string(*itr);
                    // Creates the component pointer
                    hfe::Component::ComponentPtr component(new Component(componentName));

                    if (componentType == "BlockRepeating") {
                        try {
                            unsigned int controlfld = boost::lexical_cast<unsigned int>(componentSpec["controlField"].asString());
                            hfe::Field::FieldPtr fieldPtr = this->getField(controlfld);
                            component->setControlField(fieldPtr);
                            component->setType(componentType);
                        } catch (boost::bad_lexical_cast& e) {
                            throw runtime_error("at Protocol.LoadComponents: Loading component " + string(*itr) + ", control field " + componentSpec["controlField"].asString() + " is not a valid field id.");
                        }

                    }

                    // Gets the current component's members names
                    std::vector<string> members = componentSpec["members"].getMemberNames();
                    // process the members
                    for (std::vector<string>::iterator memberItr = members.begin(); memberItr != members.end(); memberItr++) {

                        Json::Value fld = componentSpec["members"][*memberItr];

                        if (fld.empty())
                            throw runtime_error("Empty member was specified for component " + string(*itr));

                        if (string(*memberItr).empty())
                            throw runtime_error("Empty member id was specified for component " + string(*itr));

                        if (fld["isComponent"] == "Y") {
                            //Nested components
                            try {
                                hfe::Component::ComponentPtr nestedComponent = this->getComponent(*memberItr);
                                component->addNestedComponent(nestedComponent);
                            } catch (ComponentNotFound& e) {
                                pair<hfe::Component::ComponentPtr, string> depedency(component, *memberItr);
                                componentDependencies.push_back(depedency);
                            }
                        } else {
                            unsigned int field;

                            try {
                                field = boost::lexical_cast<unsigned int>(*memberItr);
                            } catch (boost::bad_lexical_cast& e) {
                                throw runtime_error("at Protocol.LoadComponents: Loading component " + string(*itr) + ", " + string(*memberItr) + " is not a valid field id.");
                            }
                            //gets the field pointer from current protocol
                            hfe::Component::FieldT fieldt;
                            fieldt.field = this->getField(field);

                            if (fieldt.field->getDataType() == "NumInGroup") {
                                stringstream msg;
                                msg << "at Protocol.LoadComponents: field " << fieldt.field->getId() << " " <<
                                        fieldt.field->getName() <<
                                        " is of type NumInGroup and cannot be assigned directly to components or messages. add the corresponding component.";
                                throw runtime_error(msg.str());

                            }
                            if (fld["isRequired"] == "Y")
                                fieldt.isRequired = true;
                            else
                                fieldt.isRequired = false;

                            // adds the field pointer to the current component
                            component->addField(fieldt);
                        }
                    }

                    this->addComponent(component);
                }
                std::vector<pair < hfe::Component::ComponentPtr, string>>::iterator depItr;
                // Stablishes all missing component dependencies
                for (depItr = componentDependencies.begin(); depItr != componentDependencies.end(); depItr++) {
                    hfe::Component::ComponentPtr dependent = depItr->first;
                    try {
                        dependent->addNestedComponent(this->getComponent(depItr->second));
                    } catch (ComponentNotFound& e) {
                        throw runtime_error("at Protocol.LoadComponents: Component dependency " + depItr->second + " was not found.");
                    }
                }
            }
        } catch (exception& e) {
            throw std::runtime_error("at Protocol.LoadComponents: " + string(e.what()));
        }
    }

    void Protocol::loadMessages() {
        try {
            if (protocolSpec["Messages"].empty()) {
                throw std::runtime_error("No messages specified for current  protocol ");
            } else {
                // gets the header and trailer specifications
                Json::Value headerSpec = protocolSpec["Components"]["StandardHeader"];
                Json::Value trailerSpec = protocolSpec["Components"]["StandardTrailer"];
                hfe::Node header(hfe::Node::ROOT_NODE);
                hfe::Node trailer(hfe::Node::ROOT_NODE);
                try {
                    populateNode(header, headerSpec, true);
                } catch (exception& e) {
                    throw std::runtime_error("Error populating header node: " + string(e.what()));
                }
                try {
                    populateNode(trailer, trailerSpec, true);
                } catch (exception& e) {
                    throw std::runtime_error("Error populating trailer node: " + string(e.what()));
                }

                //Gets the message list of the session layer
                std::vector<string> messageList = protocolSpec["Messages"].getMemberNames();
                // process the message list
                for (std::vector<string>::iterator itr = messageList.begin(); itr != messageList.end(); itr++) {
                    try {
                        hfe::Message message(*itr);
                        Json::Value bodySpec = protocolSpec["Messages"][*itr];
                        hfe::Node body(hfe::Node::ROOT_NODE);
                        populateNode(body, bodySpec, true);

                        message.setHeader(header);
                        message.setTrailer(trailer);
                        message.setBody(body);
                        messages[*itr] = message;
                    } catch (exception& e) {
                        throw std::runtime_error("Exception loading message " + *itr + " : " + string(e.what()));
                    }
                }
            }
        } catch (exception& e) {
            throw std::runtime_error("at Protocol.LoadMessages: " + string(e.what()));
        }
    }

    void Protocol::setVersion(const string ver) {
        version = ver;
    }

    string Protocol::getVersion() {
        return version;
    }

    void Protocol::setSpecification(Json::Value protSpec) {
        protocolSpec = protSpec;
    }

    hfe::Message Protocol::getMessage(string msgId) {
        //        if (messages.find(msgId) == messages.end())
        //            throw std::runtime_error("Message type " + msgId + "does not exists in protocol " + version);
        //        else
        return messages[msgId];
    }

    Json::Value& Protocol::getSpecification() {
        return protocolSpec;
    }

    void Protocol::populateNode(hfe::Node& node, Json::Value nodeSpec, bool requiredFlag) {
        try {
            node.setProtocol(this);
            Json::Value members = nodeSpec["members"];
            std::vector<string> memberList = members.getMemberNames();
            for (std::vector<string>::iterator itr = memberList.begin(); itr != memberList.end(); itr++) {
                try {
                    hfe::Node child;
                    hfe::Field::FieldPtr fieldPtr;
                    child.setProtocol(this);
                    if (members[*itr]["isComponent"] == "Y") {
                        hfe::Component::ComponentPtr componentPtr = this->getComponent(string(*itr));
                        if (componentPtr == nullptr)
                            throw std::runtime_error("Component :" + string(*itr) + " did not found.");
                        if (componentPtr->getType() == "BlockRepeating") {
                            try {
                                child.setType(hfe::Node::REPEATING_GROUP);
                                fieldPtr = componentPtr->getControlField();
                                if (fieldPtr == nullptr)
                                    throw std::runtime_error("control field for Component :" + string(*itr) + " did not found.");
                                child.setRequired(requiredFlag);
                                child.setComponent(componentPtr);
                                child.setField(fieldPtr);
                                node.appendChild(child);
                            } catch (exception& e) {
                                throw std::runtime_error("Error trying to get the id of control field :" + string(e.what()));
                            }

                        } else
                            node.resolveComponent(componentPtr);
                    } else {
                        fieldPtr = this->getField(boost::lexical_cast<unsigned int>(*itr));
                        if (fieldPtr == nullptr)
                            throw std::runtime_error("Field " + string(*itr) + " did not found.");
                        if (fieldPtr->getDataType() == "NumInGroup") {
                            stringstream msg;
                            msg << "at Protocol.LoadMessages: field " << fieldPtr->getId() << " " <<
                                    fieldPtr->getName() <<
                                    " is of type NumInGroup and cannot be assigned directly to components or messages. add the corresponding component.";
                            throw std::runtime_error(msg.str());
                        }
                        child.setType(hfe::Node::FIELD_NODE);

                        if (members[*itr]["isRequired"] == "Y")
                            child.setRequired(true);
                        else
                            child.setRequired(false);

                        child.setField(fieldPtr);
                        node.appendChild(child);

                    }
                } catch (exception& e) {
                    throw std::runtime_error("Exception populating node member " + *itr + " : " + string(e.what()));
                }
            }
        } catch (exception& e) {
            throw std::runtime_error("at populateNode: " + string(e.what()));
        }
    }

}

