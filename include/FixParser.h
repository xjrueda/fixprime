/* 
 * File:   FixParser.h
 * Author: Juan_Rueda
 *
 * Created on 9 de junio de 2015, 12:07 PM
 */

#ifndef FIXPARSER_H
#define	FIXPARSER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <stdexcept>
#include "FixDictionary.h"
#include "FixParserExceptions.h"
#include "Message.h"
#include <boost/lexical_cast.hpp>

using namespace std;
namespace hfe {

    class FixParser {
    public:
        FixParser();
        FixParser(const FixParser& orig);
        virtual ~FixParser();

        hfe::Message parseMessage(string, hfe::FixDictionary::FixDictionaryPtr);

    private:

        struct FixPair {

            FixPair(unsigned int _field, string _value) :
            field(_field), value(_value) {
            }
            unsigned int field;
            string value;
        };

        typedef map<unsigned int, FixPair> OrderedMap;
        typedef multimap<unsigned int, string> TagsMap;

        struct SerializedMessage {
            OrderedMap orderedMap;
            TagsMap tagsMap;

            string getProtocol() {
                TagsMap::iterator search = tagsMap.find(8);
                if (search != tagsMap.end())
                    return search->second;
                else
                    throw runtime_error("at SerializedMessage.getProtocol: protocol not specified.");
            }
            
            string getMsgType() {
                TagsMap::iterator search = tagsMap.find(35);
                if (search != tagsMap.end())
                    return search->second;
                else
                    throw runtime_error("at SerializedMessage.getMsgType: message type not specified.");
            }            
        };

        SerializedMessage explode(const string str, const char& ch);
        std::uint8_t checkSum(string msg);
        void parseLevel(OrderedMap&, unsigned int&, hfe::Node&);
    };
}
#endif	/* FIXPARSER_H */

