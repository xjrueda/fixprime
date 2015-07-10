/* 
 * File:   DataType.h
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 8:51 AM
 */

#ifndef DATATYPE_H
#define	DATATYPE_H

#include "DataHolderFactorySettings.h"
#include <string>
#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;

namespace fprime {

    class DataHolder {
    public:

        DataHolder() {
        }

        virtual ~DataHolder() {
        }

        typedef shared_ptr<DataHolder> DataTypePtr;

        virtual void set(string) = 0;
        virtual bool validate() = 0;
        virtual string get() = 0;

        virtual int toInt() {
            try {
                return boost::lexical_cast<int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual unsigned int toUsignedInt() {
            try {
                return boost::lexical_cast<unsigned int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual float tofloat() {
            try {
                return boost::lexical_cast<float>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual double toDouble() {
            try {
                return boost::lexical_cast<double>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long toLong() {
            try {
                return boost::lexical_cast<long>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long int toLongInt() {
            try {
                return boost::lexical_cast<long int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long double toLongDouble() {
            try {
                return boost::lexical_cast<long double>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual short toShort() {
            try {
                return boost::lexical_cast<short>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }
    protected:
        string baseData;
    };
}
#endif	/* DATATYPE_H */

