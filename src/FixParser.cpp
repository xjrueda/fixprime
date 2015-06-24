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

    bool FixParser::parseLevel(OrderedMap map, unsigned int& position, hfe::Node& node, unsigned int groupBeginning, bool isGroupInstance) {
        int instanceCounter = 0;
        for (OrderedMap::iterator it = map.find(position); it != map.end(); std::advance(it, position - (std::distance(map.begin(), it)))) {
            position++;
            Node currentNode;
            try {
                currentNode = node(it->second.field);
            } catch (InvalidField& e) {
                if (isGroupInstance) {
                    position--;
                    return true;
                } else {
                    return false;
                }
            }
            switch (currentNode.getType()) {
                case hfe::Node::FIELD_NODE:
                {
                    currentNode.setValue(it->second.value);
                    cout << currentNode.getField()->getId() << "=" << currentNode.getValue() << endl;
                    break;
                }
                case hfe::Node::REPEATING_GROUP:
                {
                    int value = boost::lexical_cast<int>(it->second.value);
                    currentNode.setValue(it->second.value);
                    FixPair fpair = map[it->first + 1];

                    for (int i = 1; i <= value; i++) {
                        //cout << "start instance " << i << endl;
                        currentNode.appendGroupInstance();
                        bool result = parseLevel(map, position, currentNode[i], fpair.field, true);
                        //cout << "end instance " << i << endl;
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

    hfe::Message FixParser::parseMessage(const string msg, hfe::FixDictionary::FixDictionaryPtr fixDictionary) {
        SerializedMessage message = explode(msg, '\001');
        hfe::Protocol::ProtocolPtr protocolPtr = fixDictionary->getProtocol(message.getProtocol());
        hfe::Message fixMessage = protocolPtr->getMessage(message.getMsgType());
        unsigned int position = 0;
        bool result = false;
        cout << "Header - position " << position << endl;
        result = parseLevel(message.orderedMap, position, fixMessage.header, 0, false);
        position--;
        cout << "Body - position " << position << endl;
        result = parseLevel(message.orderedMap, position, fixMessage.body, 0, false);
        position--;
        cout << "Trailer - position " << position << endl;
        result = parseLevel(message.orderedMap, position, fixMessage.trailer, 0, false);
        position--;
        cout << "Result = " << result << endl;
        return fixMessage;
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
                        FixPair fixPair;
                        fixPair.field = atoi(fieldTag.c_str());
                        fixPair.value = fieldValue;
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