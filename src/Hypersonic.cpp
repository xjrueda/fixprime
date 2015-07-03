/* 
 * File:   main.cpp
 * Author: DeveloperPrime
 *
 * Created on September 27, 2014, 9:43 PM
 */

#include <cstdlib>
#include <iostream>
#include "FixParser.h"
#include "Node.h"
#include "Message.h"
#include "Protocol.h"
#include "FixLoader.h"
#include "FixDictionary.h"
#include "DataTypePolicy.h"


using namespace std;

using namespace hfe;


int main(int argc, char** argv) {
    try {
        hfe::FixDictionary::FixDictionaryPtr fixDictionaryPtr(new hfe::FixDictionary);
        fixDictionaryPtr->loadProtocols("./FixSpecifications/FixVersions.json");
        
        
        hfe::Protocol::ProtocolPtr protocolPtr = fixDictionaryPtr->getProtocol("FIX.4.4");
        
  
        std::string msg = "8=FIX.4.49=00036135=849=XTRM56=02934=957=029X0552=20150612-17:14:19.33437=201506121046311=20150612_62453=4448=CC1029OBO447=C452=11448=CC1029OBO447=C452=36448=029X05447=C452=12448=029447=C452=117=53727150=039=01=P010763=148=T16U15F22=99167=FUT762=FUTU711=1309=T16305=99763=UNDL54=238=2040=244=101.9559=0151=2014=060=20150612-17:14:19.00010=099";
//        std::string msg = "8=FIX.4.49=00006835=A49=XTRM56=02934=152=20150612-17:13:10.17498=0108=10141=Y10=207";
        hfe::FixParser parser;
        parser.setProtocol(protocolPtr);
        parser.setSeparator('\001');
        
        hfe::FixParser::FlatMessage flatMessage = parser.explode(msg);
        hfe::Message fixmsg = parser.parseMessage(flatMessage);
        cout << fixmsg.toFix() << endl;
        
        cout << "Field 8  = " << fixmsg.header(8).getValue() << endl;
        cout << "Field 52  = " << fixmsg.header(52).getValue() << endl;
        cout << "Field 37  = " << fixmsg.body(37).getValue() << endl;
        
        
        cout << "Field 448 instance 1 = " << fixmsg.body(453)[1](448).getValue() << endl;
        cout << "Main finished" << endl;
        return 0;

    } catch (InvalidNodeNesting& e1) {
        cout << e1.what() << endl;
    } catch (InvalidFieldSet& e2) {
        cout << e2.what() << endl;
    } catch (InvalidValueIndex& e3) {
        cout << e3.what() << endl;
    } catch (InvalidField& e4) {
        cout << e4.what() << endl;
    } catch (InvalidGroup& e5) {
        cout << e5.what() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

}

