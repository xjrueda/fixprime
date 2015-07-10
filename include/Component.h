/* 
 * File:   Component.h
 * Author: Juan_Rueda
 *
 * Created on 27 de abril de 2015, 02:17 PM
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <cstdlib>
#include "Field.h"

using namespace std;
namespace fprime {

    class Component {
    public:
        struct FieldT {
            fprime::Field::FieldPtr field;
            bool isRequired;
        };
        typedef shared_ptr<fprime::Component> ComponentPtr;
        Component(string);
        Component(const Component& orig);
        virtual ~Component();
        
        void addField(fprime::Component::FieldT);
        void addNestedComponent(fprime::Component::ComponentPtr);
        vector<fprime::Component::FieldT> getFields();
        vector<fprime::Component::ComponentPtr> getNestedComponents();
        void setControlField(fprime::Field::FieldPtr);
        fprime::Field::FieldPtr getControlField();
        void setType(string);
        string getType();
        void removeFields();
        
        string getName();
        
    private:
        vector<fprime::Component::FieldT> fields;
        vector<fprime::Component::ComponentPtr> nestedComponents;
        fprime::Field::FieldPtr controlField;
        string name;
        string _type;
    };
}

#endif	/* COMPONENT_H */

