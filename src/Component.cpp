/* 
 * File:   Component.cpp
 * Author: Juan_Rueda
 * 
 * Created on 27 de abril de 2015, 02:17 PM
 */

#include <vector>
#include <stdexcept>

#include "Component.h"

namespace fprime {

    Component::Component(string compName): name(compName) {
    }
    
    Component::Component(const Component& orig) {
    }

    Component::~Component() {
    }
    
    void Component::addField(fprime::Component::FieldT field) {
        fields.push_back(field);
    }
    
    void Component::addNestedComponent(fprime::Component::ComponentPtr componentPtr) {
        nestedComponents.push_back(componentPtr);
    }
    void Component::setControlField(fprime::Field::FieldPtr ctrlField) {
        controlField = ctrlField;
    }
    
    fprime::Field::FieldPtr Component::getControlField() {
        if (controlField != nullptr)
            return controlField;
        else
            throw runtime_error("at Component.getControlField: Control field for component " +  name + " is null.");
    }
    
    void Component::removeFields() {
        fields.clear();
    }
    
    vector<fprime::Component::FieldT> Component::getFields() {
        return  fields;
    }
    
    vector<fprime::Component::ComponentPtr> Component::getNestedComponents() {
        return nestedComponents;
    }
    
    string Component::getName() {
        return name;
    }
    
    void Component::setType(string tpy) {
        _type = tpy;
    }
    
    string Component::getType() {
        return _type;
    }
}
