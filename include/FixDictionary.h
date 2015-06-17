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
#include <json/json.h>
#include <map>
#include <string>

namespace hfe {
    class FixDictionary {
    public:
        typedef shared_ptr<FixDictionary> FixDictionaryPtr;
        FixDictionary();
        virtual ~FixDictionary();
        void loadProtocols(string);
        hfe::Protocol::ProtocolPtr getProtocol(string);
    private:
        map<string,hfe::Protocol::ProtocolPtr> protocols;
        void loadFields(Json::Value);
    };
}
#endif	/* FIXDICTIONARY_H */

