/* 
 * File:   StringDataHolder.cpp
 * Author: Juan_Rueda
 * 
 * Created on 6 de mayo de 2015, 04:48 PM
 */

#include "StringDataHolder.h"

namespace fprime {

    StringDataHolder::StringDataHolder() {
    }

    StringDataHolder::StringDataHolder(const StringDataHolder& orig) {
    }

    StringDataHolder::~StringDataHolder() {
    }

    bool StringDataHolder::validate() {
        try {
            int tmpData = boost::lexical_cast<unsigned int>(baseData);
            if (tmpData < 0)
                return false;
            else
                nativeData = tmpData;
                return true;
        } catch (boost::bad_lexical_cast& e) {
            return false;
        }
    }

}
