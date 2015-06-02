/* 
 * File:   DataTypeFactory.cpp
 * Author: DeveloperPrime
 * 
 * Created on May 2, 2015, 9:12 AM
 */

#include "DataHolderFactory.h"

namespace hfe {

    DataHolderFactory::DataHolderFactory() {
        hfe::DataHolderFactory::DataTypes.initialize();
    }

    DataHolderFactory::DataHolderFactory(const DataHolderFactory& orig) {
    }

    DataHolderFactory::~DataHolderFactory() {
    }

    hfe::DataHolder::DataTypePtr DataHolderFactory::create(string dataTypeId) {
        try {
            hfe::DataHolder::DataTypePtr MyDataType;
            hfe::DataTypeList selectedDataType = hfe::DataHolderFactory::DataTypes.DataTypes[dataTypeId];

            if (selectedDataType != 0) {
                switch (selectedDataType) {
                    case InvalidDataType:
                    {
                        throw string("Invalid dataType call for ") + dataTypeId;
                        break;
                    }
                    case Int:
                    {
                        MyDataType.reset(new IntDataHolder);
                        break;
                    }
                    case Length:
                    case SeqNum:
                    case NumInGroup:
                    {
                        MyDataType.reset(new UIntDataHolder);
                        break;
                    }
                    case DayOfMonth:
                    case Float:
                    case Qty:
                    case Price:
                    case PriceOffset:
                    case Amt:
                    case Percentage:
                    case Char:
                    case Boolean:
                    case String:
                    case MultipleCharValue:
                    case MultipleValueString:
                    case Country:
                    case Currency:
                    case Exchange:
                    case MonthYear:
                    case UTCTimestamp:
                    case UTCTimeOnly:
                    case UTCDateOnly:
                    case LocalMktDate:
                    case TZTimeOnly:
                    case TZTimestamp:
                    case data:
                    case Pattern:
                    case Tenor:
                    case Reserved100Plus:
                    case Reserved1000Plus:
                    case Reserved4000Plus:
                    case XMLData:
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

