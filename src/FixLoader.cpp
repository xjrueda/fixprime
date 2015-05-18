/* 
 * File:   FixParser.cpp
 * Author: DeveloperPrime
 * 
 * Created on October 6, 2014, 9:03 PM
 */

#include <stdexcept>

#include "FixLoader.h"


using namespace std;

namespace hfe {

    FixLoader::FixLoader() {
    }

    FixLoader::~FixLoader() {
    }

    Json::Value FixLoader::parseFile(string fileName) {
        Json::Value root;
        Json::Reader reader;
        std::ifstream stream(fileName, std::ifstream::binary);

        bool parsingSuccessful = reader.parse(stream, root, false);

        if (!parsingSuccessful) {
            // report to the user the failure and their locations in the document.
            std::cout << "Error loading file " << fileName << ": " << reader.getFormattedErrorMessages() << endl;
            std::runtime_error("Error loading file " + fileName);
        } else {
            return root;
        }
    }
}
