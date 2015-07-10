/* 
 * File:   DataTypeFactory.cpp
 * Author: DeveloperPrime
 * 
 * Created on May 2, 2015, 9:12 AM
 */

#include "DataHolderFactory.h"

namespace fprime {

    DataHolderFactory::DataHolderFactory() {
        fprime::DataHolderFactory::DataTypes.initialize();
    }

    DataHolderFactory::DataHolderFactory(const DataHolderFactory& orig) {
    }

    DataHolderFactory::~DataHolderFactory() {
    }

    fprime::DataHolder::DataTypePtr DataHolderFactory::create(string dataTypeId) {
        try {
            fprime::DataHolder::DataTypePtr MyDataType;
            fprime::DataTypeList selectedDataType = fprime::DataHolderFactory::DataTypes.DataTypes[dataTypeId];

            if (selectedDataType != 0) {
                switch (selectedDataType) {
                    case INVALIDDATATYPE:
                    {
                        throw string("Invalid dataType call for ") + dataTypeId;
                        break;
                    }
                    case INT:
                    {
                        MyDataType.reset(new IntDataHolder);
                        break;
                    }
                    case LENGTH:
                    case SEQNUM:
                    case TAGNUM:
                    case NUMINGROUP:
                    {
                        MyDataType.reset(new UIntDataHolder);
                        break;
                    }
                    case DAYOFMONTH:
                    case FLOAT:
                    case QTY:
                    case PRICE:
                    case PRICEOFFSET:
                    case AMT:
                    case PERCENTAGE:
                    case CHAR:
                    case BOOLEAN:
                    case STRING:
                    case MULTIPLECHARVALUE:
                    case MULTIPLEVALUESTRING:
                    case COUNTRY:
                    case CURRENCY:
                    case EXCHANGE:
                    case MONTHYEAR:
                    case UTCTIMESTAMP:
                    case UTCTIMEONLY:
                    case UTCDATEONLY:
                    case LOCALMKTDATE:
                    case TZTIMEONLY:
                    case TZTIMESTAMP:
                    case DATA:
                    case PATTERN:
                    case TENOR:
                    case RESERVED100PLUS:
                    case RESERVED1000PLUS:
                    case RESERVED4000PLUS:
                    case XMLDATA:
                    {
                        MyDataType.reset(new StringDataHolder);
                        break;
                    }
                }
                return MyDataType;

            } else
                throw runtime_error("Invalid function call for " + dataTypeId);


        } catch (exception& e) {
            throw runtime_error("at DataFunctionFactory: " + string(e.what()));
        }
    }
}

