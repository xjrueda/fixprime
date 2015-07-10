/* 
 * File:   Value.cpp
 * Author: DeveloperPrime
 * 
 * Created on October 30, 2014, 2:25 PM
 */

#include "Value.h"


namespace fprime {

    Value::Value() {
    }
    
    Value::Value(string val): value(val) {
    }
    
    Value::~Value() {
    }
    
    void Value::set(string val) {
        value = val;
    }
    
    double Value::toDouble() {
        if (!value.empty()) {
            try {
                return boost::lexical_cast<double>(value);
            } catch (boost::bad_lexical_cast& badCast) {
                throw BadConvertion("Value " + value + " can't be converted to double datatype");
            }
        } else
            throw NullValue();
    }

    int Value::toInt() {
        if (!value.empty()) {
            try {
                return boost::lexical_cast<int>(value);
            } catch (boost::bad_lexical_cast& badCast) {
                throw BadConvertion("Value " + value + " can't be converted to int datatype");
            }
        } else
            throw NullValue();
    }

    string Value::toString() {
            return value;
    }

}

