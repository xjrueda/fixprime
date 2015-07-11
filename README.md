# FixPrime

FixPrime is a project (still under development), whose scope is to provide a very flexible framework to develop applications based in the fix protocol (Financial Information Exchange). 
###Currently available features in test:
 - Full customization of the specification of all fix protocol versions.
 - Message parser.
 - Message serializator.
 - Unlimited Nesting of repeating groups.

###Complete set of features planned in the project scope:
  - Full customization of the specification of all fix protocol versions.
  - Message parser.
  - Message serializator.
  - Customization of callback for Fix protocol events.
  - Automatic message sequencing.
  - Automatic session layer interaction.
  - Full message's hierarchies navigation.
  - Unlimited Nesting of repeating groups.
  - Automatic validation of Fix protocol datatypes.
  - Automatic validation of field's valid values.
  - Definition of multiple session engines
  - Behavior as Acceptor or initiator.
 
###Project's dependencies
[boost libraries] - Release 1.58.0
Download and install the boost libraries following the [boost libraries]'s site instructions.

[Jsoncpp] - Even though the project uses jsoncpp, you don't need to do anything about it, because the project has included the amalgamated version of jsoncpp source code.

###Quick Start using Fix Prime
Download and install the boost libraries following the [boost libraries]'s site instructions.
Even though the project uses jsoncpp, you don't need to do anything about it, because the project has included the amalgamated version of jsoncpp source code.

Clone the project in your system.
``` sh
git clone https://github.com/xjrueda/fixprime.git
```
Build the project using the MakeFile included.
```sh
make
```
copy the library into your local lib folder. Replace 'yourpath' for the propper path in your system.
```sh
sudo cp yourpath/fixprime/dist/Debug/GNU-Linux-x86/libsFixPrime.so /usr/local/lib
```
Start using the library.  Create a new project and link it with the libsFixPrime.so library
``` c++  
#include "FixDictionary.h"
using namespace std;
using namespace fprime;
int main(int argc, char** argv) {
    try {
        /* 
         * Instantiate  the fix dictionary.
         * You can uses a pointer to the dictionary and load all protocol 
         * specifications only once in order to be used  in all application 
         * contexts.
         * 
         * Other opcion is instantiate directly a instance of the dictionary 
         * like this:
         *  
         * FixDictionary myFixDictionary;
         */
        FixDictionary::FixDictionaryPtr fixDictionaryPtr(new FixDictionary);
        /*
         * Load the procolos defined on the folder FixSpecifications.
         * The file FixVersion contains the path for every fix protocol specification
         * Replace yourpath for your propper path in your operating system
         */
        fixDictionaryPtr->loadProtocols("yourpath/FixPrime/FixSpecifications/FixVersions.json");
        /*
         * Use the desired protocol version
         */
        Protocol::ProtocolPtr protocolPtr = fixDictionaryPtr->getProtocol("FIX.4.4");
        cout << "Protocols loaded sucessfully." << endl;
        return 0;
    } catch (const exception& e) {
        cout << "An exception has ocurred loading fix protocols: " << e.what() << endl;
    }
```



[Boost libraries]:http://www.boost.org
[Jsoncpp]:https://github.com/open-source-parsers/jsoncpp