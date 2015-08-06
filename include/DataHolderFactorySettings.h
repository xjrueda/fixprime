/*
 * Copyright (c) 2015, Juan Carlos Rueda (xjrueda@gmail.com) All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the FixMate  Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL JUAN CARLOS RUEDA BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DATATYPEFACTORYSETTINGS_H
#define	DATATYPEFACTORYSETTINGS_H

#include <map>
#include <string>
using namespace std;

namespace fprime {

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
        MULTIPLESTRINGVALUE,
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
        XMLDATA,
        LANGUAGE
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
            DataTypes["MULTIPLESTRINGVALUE"] = MULTIPLESTRINGVALUE;
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
            DataTypes["LANGUAGE"] = LANGUAGE;
        }
    };
}
#endif	/* DATATYPEFACTORYSETTINGS_H */

