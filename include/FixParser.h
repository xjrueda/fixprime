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
namespace fprime {

    class FixParser {
    public:
        FixParser();
        FixParser(const FixParser& orig);
        virtual ~FixParser();

        struct FixPair {
            unsigned int field;
            string value;
        };

        typedef map<unsigned int, FixPair> OrderedMap;
        typedef multimap<unsigned int, string> TagsMap;

        struct FlatMessage {
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
        void setProtocol(fprime::Protocol::ProtocolPtr);
        void setSeparator(char);


        fprime::FixParser::FlatMessage explode(const string str);
        std::uint8_t checkSum(string msg);

        fprime::Message parseMessage(fprime::FixParser::FlatMessage);

    private:
        fprime::Protocol::ProtocolPtr protocolPtr;



        char separator;

        bool parseLevel(OrderedMap, unsigned int&, fprime::Node&, unsigned int, bool);
    };
}
#endif	/* FIXPARSER_H */

