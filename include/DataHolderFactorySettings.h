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
        INVALIDDATATYPE,
        INT,
        LENGTH,
        TAGNUM,
        SEQNUM,
        NUMINGROUP,
        DAYOFMONTH,
        FLOAT,
        QTY,
        PRICE,
        PRICEOFFSET,
        AMT,
        PERCENTAGE,
        CHAR,
        BOOLEAN,
        STRING,
        MULTIPLECHARVALUE,
        MULTIPLEVALUESTRING,
        COUNTRY,
        CURRENCY,
        EXCHANGE,
        MONTHYEAR,
        UTCTIMESTAMP,
        UTCTIMEONLY,
        UTCDATEONLY,
        LOCALMKTDATE,
        TZTIMEONLY,
        TZTIMESTAMP,
        DATA,
        PATTERN,
        TENOR,
        RESERVED100PLUS,
        RESERVED1000PLUS,
        RESERVED4000PLUS,
        XMLDATA
    };

    typedef map<string, DataTypeList> DataTypeListType;

    struct DataTypesMap {
        DataTypeListType DataTypes;

        void initialize() {
            DataTypes["-"] = INVALIDDATATYPE;
            DataTypes["INT"] = INT;
            DataTypes["LENGTH"] = LENGTH;
            DataTypes["TAGNUM"] = TAGNUM;
            DataTypes["SEQNUM"] = SEQNUM;
            DataTypes["NUMINGROUP"] = NUMINGROUP;
            DataTypes["DAYOFMONTH"] = DAYOFMONTH;
            DataTypes["FLOAT"] = FLOAT;
            DataTypes["QTY"] = QTY;
            DataTypes["PRICE"] = PRICE;
            DataTypes["PRICEOFFSET"] = PRICEOFFSET;
            DataTypes["AMT"] = AMT;
            DataTypes["PERCENTAGE"] = PERCENTAGE;
            DataTypes["CHAR"] = CHAR;
            DataTypes["BOOLEAN"] = BOOLEAN;
            DataTypes["STRING"] = STRING;
            DataTypes["MULTIPLECHARVALUE"] = MULTIPLECHARVALUE;
            DataTypes["MULTIPLEVALUESTRING"] = MULTIPLEVALUESTRING;
            DataTypes["COUNTRY"] = COUNTRY;
            DataTypes["CURRENCY"] = CURRENCY;
            DataTypes["EXCHANGE"] = EXCHANGE;
            DataTypes["MONTHYEAR"] = MONTHYEAR;
            DataTypes["UTCTIMESTAMP"] = UTCTIMESTAMP;
            DataTypes["UTCTIMEONLY"] = UTCTIMEONLY;
            DataTypes["UTCDATEONLY"] = UTCDATEONLY;
            DataTypes["LOCALMKTDATE"] = LOCALMKTDATE;
            DataTypes["TZTIMEONLY"] = TZTIMEONLY;
            DataTypes["TZTIMESTAMP"] = TZTIMESTAMP;
            DataTypes["DATA"] = DATA;
            DataTypes["PATTERN"] = PATTERN;
            DataTypes["TENOR"] = TENOR;
            DataTypes["RESERVED100PLUS"] = RESERVED100PLUS;
            DataTypes["RESERVED1000PLUS"] = RESERVED1000PLUS;
            DataTypes["RESERVED4000PLUS"] = RESERVED4000PLUS;
            DataTypes["XMLDATA"] = XMLDATA;
        }
    };
}
#endif	/* DATATYPEFACTORYSETTINGS_H */

