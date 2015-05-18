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
namespace hfe {

    class Component {
    public:
        struct FieldT {
            hfe::Field::FieldPtr field;
            bool isRequired;
        };
//        typedef pair<FIXDF::Field::FieldPtr, bool> FieldPair;
        typedef shared_ptr<hfe::Component> ComponentPtr;
        Component(string);
        Component(const Component& orig);
        virtual ~Component();
        
        void addField(hfe::Component::FieldT);
        void addNestedComponent(hfe::Component::ComponentPtr);
        vector<hfe::Component::FieldT> getFields();
        vector<hfe::Component::ComponentPtr> getNestedComponents();
        void setControlField(hfe::Field::FieldPtr);
        hfe::Field::FieldPtr getControlField();
        void setType(string);
        string getType();
        void removeFields();
        
        string getName();
        
    private:
        vector<hfe::Component::FieldT> fields;
        vector<hfe::Component::ComponentPtr> nestedComponents;
        hfe::Field::FieldPtr controlField;
        string name;
        string _type;
    };
}

#endif	/* COMPONENT_H */

