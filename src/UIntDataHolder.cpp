/* 
 * File:   UIntDataHolder.cpp
 * Author: Juan_Rueda
 * 
 * Created on 4 de mayo de 2015, 04:51 PM
 */

#include "UIntDataHolder.h"


namespace hfe {

    UIntDataHolder::UIntDataHolder() {
    }

    UIntDataHolder::UIntDataHolder(const UIntDataHolder& orig) {
    }

    UIntDataHolder::~UIntDataHolder() {
    }

    void UIntDataHolder::set(string data) {
        baseData = data;
    }

    bool UIntDataHolder::validate() {
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

    string UIntDataHolder::get() {
        return baseData;
    }

}