/* 
 * File:   FixDictionary.h
 * Author: DeveloperPrime
 *
 * Created on October 11, 2014, 4:58 PM
 */

#ifndef FIXDICTIONARY_H
#define	FIXDICTIONARY_H

#include "Protocol.h"
#include "FixDictionaryExceptions.h"
#include "FixLoader.h"
#include "jsoncpp.h"
#include <map>
#include <string>

namespace fprime {
    class FixDictionary {
    public:
        typedef shared_ptr<FixDictionary> FixDictionaryPtr;
        FixDictionary();
        virtual ~FixDictionary();
        void loadProtocols(string);
        fprime::Protocol::ProtocolPtr getProtocol(string);
    private:
        map<string,fprime::Protocol::ProtocolPtr> protocols;
        void loadFields(Json::Value);
    };
}
#endif	/* FIXDICTIONARY_H */

