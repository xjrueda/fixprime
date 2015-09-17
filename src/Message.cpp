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

    Message::Message(const Message& org) : _id(org._id) {
        header.reset(new fprime::Node(*(org.header)));
        body.reset(new fprime::Node(*(org.body)));
        trailer.reset(new fprime::Node(*(org.trailer)));
    }

    Message::~Message() {
    }

    fprime::Node::NodePtr Message::getHeader() {
        return header;
    }

    fprime::Node::NodePtr Message::getBody() {
        return body;
    }

    fprime::Node::NodePtr Message::getTrailer() {
        return trailer;
    };

    void Message::setHeader(fprime::Node::NodePtr _header) {
        header = _header;
    }

    void Message::setBody(fprime::Node::NodePtr _body) {
        body = _body;
    }

    void Message::setTrailer(fprime::Node::NodePtr _trailer) {
        trailer = _trailer;
    }

    string Message::toFix() {
        string outputString;
        header->stringify(outputString);
        body->stringify(outputString);
        trailer->stringify(outputString);
        return outputString;
    }

    fprime::Message& Message::operator=(fprime::Message& other) {
        header.reset(new fprime::Node(*(other.header)));
        body.reset(new fprime::Node(*(other.body)));
        trailer.reset(new fprime::Node(*(other.trailer)));
        _id = other._id;
        return *this;
    }

}

