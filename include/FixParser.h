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
#include "Node.h"
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
            unsigned int bodylength = 0;
            unsigned int checkSum = 0;

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
        bool parseLevel(OrderedMap, unsigned int&, fprime::Node::NodePtr, unsigned int, bool);
    };
}
#endif	/* FIXPARSER_H */

