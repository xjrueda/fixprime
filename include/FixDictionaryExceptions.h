/* 
 * File:   FixDictionaryExceptions.h
 * Author: DeveloperPrime
 *
 * Created on October 11, 2014, 6:32 PM
 */

#ifndef FIXDICTIONARYEXCEPTIONS_H
#define	FIXDICTIONARYEXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

namespace hfe {

    class NoProtocolsFound : public exception {
    public:

        NoProtocolsFound() {
        }

        ~NoProtocolsFound() throw () {
        }

        const string what() throw () {
            return "No protocol was found to load";
        }
    };
}

#endif	/* FIXDICTIONARYEXCEPTIONS_H */

