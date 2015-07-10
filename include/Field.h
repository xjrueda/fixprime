/* 
 * File:   Field.h
 * Author: DeveloperPrime
 *
 * Created on September 29, 2014, 9:56 PM
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

