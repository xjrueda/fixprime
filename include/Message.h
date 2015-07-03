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

namespace hfe {

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
        
        hfe::Node header;
        hfe::Node body;
        hfe::Node trailer;
        
        hfe::Node& getHeader();
        hfe::Node& getBody();
        hfe::Node& getTrailer();

        void setHeader(hfe::Node);
        void setBody(hfe::Node);
        void setTrailer(hfe::Node);
        string toFix();
    private:
//        FIXDF::Node header;
//        FIXDF::Node body;
//        FIXDF::Node trailer;
        string _id;
    };
}
#endif	/* MESSAGETEMPLATE_H */

