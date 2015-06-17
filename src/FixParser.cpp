/* 
 * File:   FixParser.cpp
 * Author: Juan_Rueda
 * 
 * Created on 9 de junio de 2015, 12:07 PM
 */

#include "FixParser.h"


namespace hfe {

    FixParser::FixParser() {
    }

    FixParser::FixParser(const FixParser& orig) {
    }

    FixParser::~FixParser() {
    }

    void FixParser::parseLevel(OrderedMap& map, unsigned int& position, hfe::Node& node) {
  
        for (OrderedMap::iterator it = map.find(position); it != map.end(); it++)  {
            position++;
            
            switch (node(it->second.field).getType()) {
                case hfe::Node::FIELD_NODE:
                {
                    try {
                        node(it->second.field).setValue(it->second.value);
                    } catch (InvalidField& e) {
                        cout << "Field is not of in current Node" << endl;
                    }
                    break;
                }
                case hfe::Node::REPEATING_GROUP:
                {
                    unsigned int value = boost::lexical_cast<unsigned int>(it->second.value);
                    // process all instances
                    //TODO:  Determine the initial field of repeating group
                    for (unsigned int i = 1;i <= value; i++) {
                        node(it->second.field).appendGroupInstance();
                        parseLevel(map, position, node(it->second.field)[i]); 
                    }
                    break;
                }
            }
        }
    }
    
    hfe::Message FixParser::parseMessage(const string msg, hfe::FixDictionary::FixDictionaryPtr fixDictionary) {
        SerializedMessage message = explode(msg, '\001');
        hfe::Protocol::ProtocolPtr protocolPtr = fixDictionary->getProtocol(message.getProtocol());
        hfe::Message fixMessage = protocolPtr->getMessage(message.getMsgType());

        //process header

        for (OrderedMap::iterator it = message.orderedMap.begin(); it != message.orderedMap.end(); it++) {

            switch (fixMessage.header(it->second.field).getType()) {
                case hfe::Node::FIELD_NODE:
                {
                    try {
                        fixMessage.header(it->second.field).setValue(it->second.value);
                    } catch (InvalidField& e) {
                        cout << "Field is not of head" << e.what() << endl;
                    }
                    break;
                }
                case hfe::Node::REPEATING_GROUP:
                {
                    break;
                }
            }

        }

    }

    hfe::FixParser::SerializedMessage FixParser::explode(const string str, const char& ch) {
        string next;
        hfe::FixParser::SerializedMessage result;
        unsigned int position = 0;

        // For each character in the string
        for (string::const_iterator it = str.begin(); it != str.end(); it++) {
            // If we've hit the terminal character
            if (*it == ch) {
                // If we have some characters accumulated
                if (!next.empty()) {
                    string fieldTag, fieldValue;
                    size_t found = next.find("=");
                    if (found != std::string::npos) {
                        fieldTag = next.substr(0, found);
                        fieldValue = next.substr(found + 1, next.size());
                        // Add them to the result multimap
                        FixPair fixPair(atoi(fieldTag.c_str()), fieldValue);
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
        return result;
    }

    std::uint8_t FixParser::checkSum(string msg) {
        size_t startPos = msg.find("8=FIX");
        if (startPos == string::npos)
            throw runtime_error("begin string did not found");
        size_t endPos = msg.find("\00110=") + 1;
        if (endPos == string::npos)
            throw runtime_error("Checksum field did not found");
        string _msg = msg.substr(startPos, msg.size() - (msg.size() - endPos));
        printf("startpos %d endpos %d", startPos, endPos);
        uint8_t cs = std::accumulate(_msg.begin(), _msg.end(), static_cast<std::uint8_t> (0));
        return cs % 256;
    }
}