/* 
 * File:   FixParser.h
 * Author: DeveloperPrime
 *
 * Created on October 6, 2014, 9:03 PM
 */

#ifndef FIXPARSER_H
#define	FIXPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <json/json.h>

using namespace std;

namespace fprime {

    class FixLoader {
    public:
        FixLoader();
        virtual ~FixLoader();
        Json::Value parseFile(string);
    };
}
#endif	/* FIXPARSER_H */

