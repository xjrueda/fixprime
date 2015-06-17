/* 
 * File:   FixDictionary.cpp
 * Author: DeveloperPrime
 * 
 * Created on October 11, 2014, 4:58 PM
 */

#include "FixDictionary.h"

namespace hfe {

    FixDictionary::FixDictionary() {
    }

    FixDictionary::~FixDictionary() {
    }

    void FixDictionary::loadProtocols(string fileName) {
        FixLoader loader;
        Json::Value protocolList = loader.parseFile(fileName);
        if (protocolList.empty()) {
            throw std::runtime_error("Protocol list could not be load");
        } else {
            // Process the protocol list
             std::vector<string> protocolNames = protocolList.getMemberNames();
             
            for (std::vector<string>::iterator itr = protocolNames.begin(); itr != protocolNames.end(); itr++) {
                string protocolSpecFile = protocolList[*itr]["dataFile"].asString();
                Json::Value protocolSpec = loader.parseFile(protocolSpecFile);
                
                if (protocolSpec.empty()) {
                    throw std::runtime_error("Protocol " +  *itr + " could not be load");
                } else {
                    try {
                    hfe::Protocol::ProtocolPtr protocol(new hfe::Protocol); 
                    protocol->setSpecification(protocolSpec);
                    protocol->setVersion(*itr);
                    protocols[*itr] = protocol;
                    protocol->load();
                    } catch (exception& e) {
                        throw std::runtime_error("Protocol " +  *itr + " could not be load. Reason: " + e.what());
                    }
                }
                
            }
            //////////////////////////////
            
        } 
    }
    
    hfe::Protocol::ProtocolPtr FixDictionary::getProtocol(string version) {
        map<string,hfe::Protocol::ProtocolPtr>::iterator search;
        search = protocols.find(version);
        if (search != protocols.end())
            return search->second;
        else
            throw std::runtime_error("at FixDictionary.getProtocol: Protocol " + version + " does not exists in dictionary");
 
    }
}

