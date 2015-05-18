/* 
 * File:   DataTypePolicy.h
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 7:04 AM
 */

#ifndef DATATYPEPOLICY_H
#define	DATATYPEPOLICY_H

#include <iostream>

template <typename DataTypePolicy>
class DataType1 : private DataTypePolicy {
    using DataTypePolicy::validate;

public:
    // Behaviour method

    bool run() {
        // Two policy methods
        return validate();
    }
};

class TagNumPolicy {
protected:
    bool validate() {
        return true;
    }
};

class LengthPolicy {
protected:
    bool validate() {
        return false;
    }
};


#endif	/* DATATYPEPOLICY_H */

