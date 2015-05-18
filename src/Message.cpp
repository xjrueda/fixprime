/* 
 * File:   MessageTemplate.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:15 PM
 */

#include "Message.h"

namespace hfe {

    Message::Message() {
    }
    Message::Message(const string msgId) {
        _id = msgId;
    }

    //    MessageTemplate::MessageTemplate(const MessageTemplate& orig) {
    //    }

    Message::~Message() {
    }

    hfe::Node& Message::getHeader() {
        return header;
    }

    hfe::Node& Message::getBody() {
        return body;
    }

    hfe::Node& Message::getTrailer() {
        return trailer;
    };

    void Message::setHeader(hfe::Node _header) {
        header = _header;
    }

    void Message::setBody(hfe::Node _body) {
        body = _body;
    }

    void Message::setTrailer(hfe::Node _trailer) {
        trailer = _trailer;
    }
    
    
    string Message::stringify() {
        string outputString;
        string separator = "\001";
        //header->stringify(outputString, separator, 0);
        //body->stringify(outputString, separator, 0);
        //trailer->stringify(outputString, separator, 0);
        
        return outputString;
    }

}

