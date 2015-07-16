/* 
 * File:   FixParser.cpp
 * Author: Juan_Rueda
 * 
 * Created on 9 de junio de 2015, 12:07 PM
 */

#include <mutex>

#include "FixParser.h"


namespace fprime {

    FixParser::FixParser() {
        separator = '\001';
    }

    FixParser::FixParser(const FixParser& orig) {
    }

    FixParser::~FixParser() {
    }

    void FixParser::setProtocol(fprime::Protocol::ProtocolPtr protPtr) {
        protocolPtr = protPtr;
    }

    void FixParser::setSeparator(char sepChar) {
        separator = sepChar;
    }

    bool FixParser::parseLevel(OrderedMap map, unsigned int& position, fprime::Node& node, unsigned int groupBeginning, bool isGroupInstance) {
        int instanceCounter = 0;
        for (OrderedMap::iterator it = map.find(position); it != map.end(); std::advance(it, position - (std::distance(map.begin(), it)))) {
            position++;
            try {
                string val = node(it->second.field).getValue();
            } catch (InvalidField& e) {
                position--;
                if (isGroupInstance) {
                    return true;
                } else {
                    return false;
                }
            }
            switch (node(it->second.field).getType()) {
                case fprime::Node::FIELD_NODE:
                {
                    node(it->second.field).setValue(it->second.value);
                    break;
                }
                case fprime::Node::REPEATING_GROUP:
                {
                    int value = boost::lexical_cast<unsigned int>(it->second.value);
                    node(it->second.field).setValue(it->second.value);
                    FixPair fpair = map[it->first + 1];

                    for (unsigned int i = 1; i <= value; i++) {
                        node(it->second.field).appendGroupInstance();
                        bool result = parseLevel(map, position, node(it->second.field)[i], fpair.field, true);
                    }
                    break;
                }
            }
            if (isGroupInstance) {
                if (groupBeginning == map[it->first + 1].field) {
                    return true;
                }
            }
        }
    }

    fprime::Message FixParser::parseMessage(fprime::FixParser::FlatMessage message) {
        fprime::Message fixMessage = protocolPtr->getMessage(message.getMsgType());
        unsigned int position = 0;
        bool result = false;
        result = parseLevel(message.orderedMap, position, fixMessage.header, 0, false);
        result = parseLevel(message.orderedMap, position, fixMessage.body, 0, false);
        result = parseLevel(message.orderedMap, position, fixMessage.trailer, 0, false);
        return fixMessage;
    }

    fprime::FixParser::FlatMessage FixParser::explode(const string str) {
        string next;
        fprime::FixParser::FlatMessage result;
        unsigned int position = 0;
        unsigned int bodyLength = 0;
        bool inBody = false;
        // For each character in the string
        for (string::const_iterator it = str.begin(); it != str.end(); it++) {
            // If we've hit the terminal character
            if (*it == separator) {
                // If we have some characters accumulated
                if (!next.empty()) {
                    string fieldTag, fieldValue;
                    size_t found = next.find("=");
                    if (found != std::string::npos) {
                        fieldTag = next.substr(0, found);
                        fieldValue = next.substr(found + 1, next.size());
                        // Add them to the result multimap
                        FixPair fixPair;
                        fixPair.field = atoi(fieldTag.c_str());
                        fixPair.value = fieldValue;

                        if (fixPair.field == 35 && !inBody)
                            inBody = true;
                        if (fixPair.field == 10 && inBody)
                            inBody = false;

                        if (inBody) {
                            bodyLength += string(fieldTag.c_str()).size() + fixPair.value.size() + 2;
                        }
                        result.orderedMap.insert(pair<unsigned int, FixPair>(position, fixPair));
                        result.tagsMap.insert(pair<unsigned int, string>(atoi(fieldTag.c_str()), fieldValue));
                        next.clear();
                        position++;
                    }

                }
            } else {
                // Accumulate the next character into the sequence
                next += *it;
            }
        }
        result.bodylength = bodyLength;
        result.checkSum = checkSum(str);
        return result;
    }

    std::uint8_t FixParser::checkSum(string msg) {
        size_t startPos = msg.find("8=FIX");
        if (startPos == string::npos)
            throw runtime_error("at FixParser.checkSum: begin string did not found");
        size_t endPos = msg.find("\00110=") + 1;
        if (endPos == string::npos)
            throw runtime_error("at FixParser.checkSum: Checksum field did not found");
        string _msg = msg.substr(startPos, msg.size() - (msg.size() - endPos));
        uint8_t cs = std::accumulate(_msg.begin(), _msg.end(), static_cast<std::uint8_t> (0));
        return cs % 256;
    }
}