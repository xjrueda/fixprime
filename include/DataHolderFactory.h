/* 
 * File:   DataTypeFactory.h
 * Author: DeveloperPrime
 *
 * Created on May 2, 2015, 9:12 AM
 */

#ifndef DATATYPEFACTORY_H
#define	DATATYPEFACTORY_H

#include "DataHolder.h"
#include "DataHolderFactorySettings.h"
#include "IntDataHolder.h"
#include "UIntDataHolder.h"
#include "StringDataHolder.h"

namespace fprime {

    class DataHolderFactory {
    public:
        DataHolderFactory();
        DataHolderFactory(const DataHolderFactory& orig);
        virtual ~DataHolderFactory();
        fprime::DataHolder::DataTypePtr create(string);
    private:
        DataTypesMap DataTypes;
    };
}
#endif	/* DATATYPEFACTORY_H */

