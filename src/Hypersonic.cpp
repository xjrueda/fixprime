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
        //        hfe::FixDictionary fixDictionary;
        //        fixDictionary.loadProtocols("/apps/Dev/NetBeansProjects/Hypersonic/FixSpecifications/FixVersions.json");
        //        hfe::Protocol::ProtocolPtr fix44 = fixDictionary.getProtocol("FIX 4.4");
        //
        //        hfe::Message msg = fix44->getMessage("D");
        //        msg.header(8).setValue("FIX 4.4");
        //
        //        cout << "Value for field 453 = " << msg.body(453).getValue() << endl;
        //        cout.flush();
        //        msg.body(453).appendGroupInstance();
        //
        //        msg.body(453)[1](448).setValue("Cuatro");
        //        msg.body(453)[1](803).setValue("Ocho");

        hfe::FixDictionary::FixDictionaryPtr fixDictionaryPtr(new hfe::FixDictionary);
        fixDictionaryPtr->loadProtocols("./FixSpecifications/FixVersions.json");
        std::string msg = "8=FIX.4.49=10335=A34=149=02950=029X0552=20150612-17:13:07.77856=XTRM98=0108=10141=Y553=CC1029OBO554=ZXC45610=189";

        hfe::FixParser parser;

        hfe::Message fixmsg = parser.parseMessage(msg, fixDictionaryPtr);
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

