/* 
 * File:   MessageTemplate.cpp
 * Author: DeveloperPrime
 * 
 * Created on September 29, 2014, 9:15 PM
 */

#include "Message.h"
#include "FixParser.h"

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
        string strHeader, strBody, strTrailer, strDummy;

        unsigned int bodyLength = 0;
        unsigned int dummy = 0;
        bool isBody = false;

        header->stringify(strDummy, isBody, bodyLength);
        body->stringify(strBody, isBody, bodyLength);
        header->getChild(9)->setValue(boost::lexical_cast<string>(bodyLength));
        header->stringify(strHeader, isBody, dummy);
        trailer->stringify(strTrailer, isBody, dummy);

        //calculate checksum
        fprime::FixParser fparser;
        unsigned int checkSum = fparser.checkSum(strHeader + strBody + strTrailer);
        
        stringstream ssCheckSum;
        ssCheckSum << std::setw (3) << std::setfill('0')<< checkSum;
        trailer->getChild(10)->setValue(ssCheckSum.str());
        isBody = false;
        strTrailer.clear();
        trailer->stringify(strTrailer, isBody, dummy);
        return strHeader + strBody + strTrailer;
    }

    fprime::Message& Message::operator=(fprime::Message& other) {
        header.reset(new fprime::Node(*(other.header)));
        body.reset(new fprime::Node(*(other.body)));
        trailer.reset(new fprime::Node(*(other.trailer)));
        _id = other._id;
        return *this;
    }

}

