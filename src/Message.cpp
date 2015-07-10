/* 
 * File:   MessageTemplate.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:15 PM
 */

#include "Message.h"

namespace fprime {

    Message::Message() {
    }
    Message::Message(const string msgId) {
        _id = msgId;
    }

    //    MessageTemplate::MessageTemplate(const MessageTemplate& orig) {
    //    }

    Message::~Message() {
    }

    fprime::Node& Message::getHeader() {
        return header;
    }

    fprime::Node& Message::getBody() {
        return body;
    }

    fprime::Node& Message::getTrailer() {
        return trailer;
    };

    void Message::setHeader(fprime::Node _header) {
        header = _header;
    }

    void Message::setBody(fprime::Node _body) {
        body = _body;
    }

    void Message::setTrailer(fprime::Node _trailer) {
        trailer = _trailer;
    }
    
    
    string Message::toFix() {
        string outputString;
        header.stringify(outputString);
        body.stringify(outputString);
        trailer.stringify(outputString);
        return outputString;
    }

}

