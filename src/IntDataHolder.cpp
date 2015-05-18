/* 
 * File:   IntDataType.cpp
 * Author: DeveloperPrime
 * 
 * Created on May 2, 2015, 9:55 AM
 */

#include "IntDataHolder.h"


namespace hfe {

    IntDataHolder::IntDataHolder() {
    }

    IntDataHolder::IntDataHolder(const IntDataHolder& orig) {
    }

    IntDataHolder::~IntDataHolder() {
    }

    void IntDataHolder::set(string data) {
        baseData = data;
    }

    bool IntDataHolder::validate() {
        try {
            nativeData = boost::lexical_cast<int>(baseData);
            return true;
        } catch (boost::bad_lexical_cast& e) {
            return false;
        }
    }
      
    string IntDataHolder::get() {
        return baseData;
    }
}
