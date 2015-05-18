/* 
 * File   DataTypeFactorySettings.h
 * Author DeveloperPrime
 *
 * Created on May 2, 2015, 828 AM
 */

#ifndef DATATYPEFACTORYSETTINGS_H
#define	DATATYPEFACTORYSETTINGS_H

#include <map>
#include <string>
using namespace std;

namespace hfe {

    enum DataTypeList {
        InvalidDataType,
        Int,
        Length,
        TagNum,
        SeqNum,
        NumInGroup,
        DayOfMonth,
        Float,
        Qty,
        Price,
        PriceOffset,
        Amt,
        Percentage,
        Char,
        Boolean,
        String,
        MultipleCharValue,
        MultipleStringValue,
        Country,
        Currency,
        Exchange,
        MonthYear,
        UTCTimestamp,
        UTCTimeOnly,
        UTCDateOnly,
        LocalMktDate,
        TZTimeOnly,
        TZTimestamp,
        data,
        Pattern,
        Tenor,
        Reserved100Plus,
        Reserved1000Plus,
        Reserved4000Plus,
        XMLData
    };

    typedef map<string, DataTypeList> DataTypeListType;

    struct DataTypesMap {
        DataTypeListType DataTypes;

        void initialize() {
            DataTypes["-"] = InvalidDataType;
            DataTypes["Int"] = Int;
            DataTypes["Length"] = Length;
            DataTypes["TagNum"] = TagNum;
            DataTypes["SeqNum"] = SeqNum;
            DataTypes["NumInGroup"] = NumInGroup;
            DataTypes["DayOfMonth"] = DayOfMonth;
            DataTypes["float"] = Float;
            DataTypes["Qty"] = Qty;
            DataTypes["Price"] = Price;
            DataTypes["PriceOffset"] = PriceOffset;
            DataTypes["Amt"] = Amt;
            DataTypes["Percentage"] = Percentage;
            DataTypes["char"] = Char;
            DataTypes["Boolean"] = Boolean;
            DataTypes["String"] = String;
            DataTypes["MultipleCharValue"] = MultipleCharValue;
            DataTypes["MultipleStringValue"] = MultipleStringValue;
            DataTypes["Country"] = Country;
            DataTypes["Currency"] = Currency;
            DataTypes["Exchange"] = Exchange;
            DataTypes["MonthYear"] = MonthYear;
            DataTypes["UTCTimestamp"] = UTCTimestamp;
            DataTypes["UTCTimeOnly"] = UTCTimeOnly;
            DataTypes["UTCDateOnly"] = UTCDateOnly;
            DataTypes["LocalMktDate"] = LocalMktDate;
            DataTypes["TZTimeOnly"] = TZTimeOnly;
            DataTypes["TZTimestamp"] = TZTimestamp;
            DataTypes["data"] = data;
            DataTypes["Pattern"] = Pattern;
            DataTypes["Tenor"] = Tenor;
            DataTypes["Reserved100Plus"] = Reserved100Plus;
            DataTypes["Reserved1000Plus"] = Reserved1000Plus;
            DataTypes["Reserved4000Plus"] = Reserved4000Plus;
            DataTypes["XMLData"] = XMLData;
        }
    };
}
#endif	/* DATATYPEFACTORYSETTINGS_H */

