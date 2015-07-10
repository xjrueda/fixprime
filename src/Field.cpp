/* 
 * File:   Field.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:56 PM
 */

#include <iostream>
#include <stdexcept>
#include "Field.h"
#include "Component.h"



using namespace std;

namespace fprime {

    //    Field::Field() {
    //    }

    Field::Field(unsigned int id) {
        if (id)
            _id = id;
        else
            throw std::runtime_error("at Field.Constructor attribute could not be empty.");
    }

    Field::~Field() {
    }

    void Field::setId(unsigned int id) {
        if (id)
            _id = id;
        else
            throw std::runtime_error("at Field.setId: Id attribute could not be empty.");
    }

    void Field::setName(string name) {
        if (!name.empty())
            _name = name;
        else
            throw std::runtime_error("at Field.setName: Name attribute could not be empty.");
    }

    void Field::setDataType(string dataType) {
        if (!dataType.empty())
            _dataType = dataType;
        else
            throw std::runtime_error("at Field.setDataType: DataType attribute could not be empty.");

    }

    unsigned int Field::getId() {
        if (_id)
            return _id;
        else
            throw std::runtime_error("at Field.getId: Id attribute is empty.");
    }

    string Field::getName() {
        if (!_name.empty())
            return _name;
        else
            throw std::runtime_error("at Field.getName: Name attribute is empty.");
    }

    string Field::getDataType() {
        if (!_dataType.empty())
            return _dataType;
        else
            throw std::runtime_error("at Field.getDataType: DataType attribute is empty.");
    }

    void Field::addValidValue(string val, string desc) {
        if (!val.empty()) {
            _validValues[val] = desc;
        } else
            throw std::runtime_error("at Field.addValidValue: valid value attribute could not be empty.");
    }

    bool Field::validateValidValue(string val) {
        map<string, string>::iterator search = _validValues.find(val);
        if (search != _validValues.end())
            return true;
        else
            return false;
    }


}