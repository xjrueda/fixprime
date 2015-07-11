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

#ifndef FIELD_H
#define	FIELD_H

#include <string>
#include <map>
#include <memory>
#include "jsoncpp.h"

using namespace std;

namespace fprime {
    class Component;
    class Field {
    public:
        typedef std::shared_ptr<fprime::Field> FieldPtr;
        enum FieldDataType {
            Amt,
            Boolean,
            Char,
            Country,
            Currency,
            Data,
            Day_of_month,
            Exchange,
            Float,
            Int,
            Length,
            LocalMktDate,
            MonthYear,
            MultiValueString,
            NumInGroup,
            Percentage,
            Price,
            PriceOffset,
            Qty,
            SeqNum,
            String,
            TagNum,
            UTCDateOnly,
            UTCTimeOnly,
            UTCTimestamp
        };
        //        Field();
        Field(unsigned int id);
        virtual ~Field();
        void setId(unsigned int);
        void setName(string);
        void setDataType(string);
        unsigned int getId();
        string getName();
        string getDataType();
        void addValidValue(string, string);
        bool validateValidValue(string);
    private:
        unsigned int _id;
        string _name;
        string _dataType;
        map<string, string> _validValues;
        map<unsigned int, bool> _children;
//        FIXDF::Component* componentPtr;
    };
}

#endif	/* FIELD_H */

