/* 
 * File:   Value.h
 * Author: DeveloperPrime
 *
 * Created on October 30, 2014, 2:25 PM
 */

#ifndef VALUE_H
#define	VALUE_H

#include <boost/lexical_cast.hpp>
#include <string>
#include "FixParserExceptions.h"

using namespace std;

namespace fprime {

    class Value {
    public:
        Value();
        Value(string);
        virtual ~Value();
        void set(string);
        double toDouble();
        int toInt();
        string toString();
    private:
        string value;
    };
}
#endif	/* VALUE_H */

