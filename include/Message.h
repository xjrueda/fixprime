/* 
 * File:   MessageTemplate.h
 * Author: DeveloperPrime
 *
 * Created on September 29, 2014, 9:15 PM
 */

#ifndef MESSAGETEMPLATE_H
#define	MESSAGETEMPLATE_H

#include "Node.h"

using namespace std;

namespace fprime {

    class Message {
    public:
        Message();
        Message(const string);
//        MessageTemplate(const MessageTemplate& orig);
        virtual ~Message();
        enum MessageLevel {
            APPLICATION,
            SESSION
        };
        
        fprime::Node header;
        fprime::Node body;
        fprime::Node trailer;
        
        fprime::Node& getHeader();
        fprime::Node& getBody();
        fprime::Node& getTrailer();

        void setHeader(fprime::Node);
        void setBody(fprime::Node);
        void setTrailer(fprime::Node);
        string toFix();
    private:
//        FIXDF::Node header;
//        FIXDF::Node body;
//        FIXDF::Node trailer;
        string _id;
    };
}
#endif	/* MESSAGETEMPLATE_H */

