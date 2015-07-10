/* 
 * File:   IntDataType.h
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 9:55 AM
 */

#ifndef INTDATATYPE_H
#define	INTDATATYPE_H

#include "DataHolder.h"

namespace fprime {

    class IntDataHolder : public fprime::DataHolder {
    public:
        IntDataHolder();
        IntDataHolder(const IntDataHolder& orig);
        virtual ~IntDataHolder();

        void set(string);
        bool validate();
        string get();
    private:
        int nativeData;
    };
}
#endif	/* INTDATATYPE_H */

