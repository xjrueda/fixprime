/* 
 * File:   Protocol.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:13 PM
 */

#include "Protocol.h"
#include "Component.h"

namespace fprime {

    Protocol::Protocol() {
    }

    Protocol::~Protocol() {
        //        cout << "Protocol " << version << " released" << endl;
    }

    void Protocol::addField(fprime::Field::FieldPtr field) {
        fields[field->getId()] = field;
    }

    void Protocol::addComponent(fprime::Component::ComponentPtr component) {
        components[component->getName()] = component;
    }

    fprime::Component::ComponentPtr Protocol::getComponent(string compName) {
        auto search = components.find(compName);
        if (search == components.end())
            throw ComponentNotFound(compName);
        else
            return search->second;
    }

    fprime::Field::FieldPtr Protocol::getField(unsigned int id) {
        map<unsigned int, fprime::Field::FieldPtr >::iterator search;
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
                        fprime::Field::FieldPtr field(new fprime::Field(boost::lexical_cast<unsigned int>(*itr)));
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

                vector<pair < fprime::Component::ComponentPtr, string>> componentDependencies;
                std::vector<string> names = protocolSpec["Components"].getMemberNames();
                // Process the components
                for (std::vector<string>::iterator itr = names.begin(); itr != names.end(); itr++) {
                    //gets the component json Value
                    Json::Value componentSpec = protocolSpec["Components"][*itr];

                    //gets the component's properties
                    string componentType = componentSpec["type"].asString();

                    string componentName = string(*itr);
                    // Creates the component pointer
                    fprime::Component::ComponentPtr component(new Component(componentName));

                    if (componentType == "BlockRepeating") {
                        try {
                            unsigned int controlfld = boost::lexical_cast<unsigned int>(componentSpec["controlField"].asString());
                            fprime::Field::FieldPtr fieldPtr = this->getField(controlfld);
                            component->setControlField(fieldPtr);
                            component->setType(componentType);
                        } catch (boost::bad_lexical_cast& e) {
                            throw runtime_error("Exception loading component " + string(*itr) + ", control field " + componentSpec["controlField"].asString() + " is not a valid field id.");
                        }

                    }

                    // Gets the current component's members array
                    Json::Value members = componentSpec["members"];
                    if (!members.isArray())
                        throw runtime_error("at Protocol.LoadComponents: component " + string(*itr) + " does not have a member array.");


                    // process the members
                    for (int i = 0; i < members.size(); i++) {

                        Json::Value fld = members[i];

                        if (fld.empty())
                            throw runtime_error("Empty member was specified for component " + string(*itr));

                        if (fld["memberId"].empty())
                            throw runtime_error("No memberId was specified in member list of component " + string(*itr));

                        string memberId = fld["memberId"].asString();

                        if (fld["isComponent"] == "Y") {
                            //Nested components
                            try {
                                fprime::Component::ComponentPtr nestedComponent = this->getComponent(memberId);
                                component->addNestedComponent(nestedComponent);
                            } catch (ComponentNotFound& e) {
                                pair<fprime::Component::ComponentPtr, string> depedency(component, memberId);
                                componentDependencies.push_back(depedency);
                            }
                        } else {
                            unsigned int field;

                            try {
                                field = boost::lexical_cast<unsigned int>(memberId);
                            } catch (boost::bad_lexical_cast& e) {
                                throw runtime_error("exception loading component " + string(*itr) + ", " + memberId + " is not a valid field id.");
                            }
                            //gets the field pointer from current protocol
                            fprime::Component::FieldT fieldt;
                            fieldt.field = this->getField(field);

                            if (fieldt.field->getDataType() == "NumInGroup") {
                                stringstream msg;
                                msg << "field " << fieldt.field->getId() << " " <<
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
                std::vector<pair < fprime::Component::ComponentPtr, string>>::iterator depItr;
                // Stablishes all missing component dependencies
                for (depItr = componentDependencies.begin(); depItr != componentDependencies.end(); depItr++) {
                    fprime::Component::ComponentPtr dependent = depItr->first;
                    try {
                        dependent->addNestedComponent(this->getComponent(depItr->second));
                    } catch (ComponentNotFound& e) {
                        throw runtime_error("Component dependency " + depItr->second + " was not found.");
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
                fprime::Node header(fprime::Node::ROOT_NODE);
                fprime::Node trailer(fprime::Node::ROOT_NODE);
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
                        fprime::Message message(*itr);
                        Json::Value bodySpec = protocolSpec["Messages"][*itr];
                        fprime::Node body(fprime::Node::ROOT_NODE);
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

    fprime::Message Protocol::getMessage(string msgId) {
        map<const string, fprime::Message>::iterator search;
        search = messages.find(msgId);
        if (search != messages.end())
            return search->second;
        else
            throw std::runtime_error("at Protocol.getMessage: Message type " + msgId + " does not exists in protocol " + version);

    }

    Json::Value& Protocol::getSpecification() {
        return protocolSpec;
    }

    void Protocol::populateNode(fprime::Node& node, Json::Value nodeSpec, bool requiredFlag) {
        try {
            node.setProtocol(this);
            Json::Value members = nodeSpec["members"];
            for (int i = 0; i < members.size(); i++) {
                string memberId = members[i]["memberId"].asString();
                try {
                    if (memberId.empty())
                        throw runtime_error("Empty member was specified for node.");

                    fprime::Node child;
                    fprime::Field::FieldPtr fieldPtr;
                    child.setProtocol(this);

                    if (members[i]["isComponent"] == "Y") {

                        fprime::Component::ComponentPtr componentPtr = this->getComponent(string(memberId));
                        if (componentPtr == nullptr)
                            throw std::runtime_error("Component :" + memberId + " did not found.");
                        if (componentPtr->getType() == "BlockRepeating") {
                            try {
                                child.setType(fprime::Node::REPEATING_GROUP);
                                fieldPtr = componentPtr->getControlField();
                                if (fieldPtr == nullptr)
                                    throw std::runtime_error("control field for Component :" + memberId + " did not found.");
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
                        fieldPtr = this->getField(boost::lexical_cast<unsigned int>(memberId));
                        if (fieldPtr == nullptr)
                            throw std::runtime_error("Field " + memberId + " did not found.");
                        if (fieldPtr->getDataType() == "NumInGroup") {
                            stringstream msg;
                            msg << fieldPtr->getId() << " " <<
                                    fieldPtr->getName() <<
                                    " is of type NumInGroup and cannot be assigned directly to components or messages. add the corresponding component.";
                            throw std::runtime_error(msg.str());
                        }
                        child.setType(fprime::Node::FIELD_NODE);

                        if (members[i]["isRequired"] == "Y")
                            child.setRequired(true);
                        else
                            child.setRequired(false);

                        child.setField(fieldPtr);
                        node.appendChild(child);

                    }
                } catch (exception& e) {
                    throw std::runtime_error("Exception populating node member " + memberId + " : " + string(e.what()));
                }
            }
        } catch (exception& e) {
            throw std::runtime_error("at populateNode: " + string(e.what()));
        }
    }

}

