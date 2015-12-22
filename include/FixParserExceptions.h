/*
 * Copyright (c) 2015, Juan Carlos Rueda (xjrueda@gmail.com) All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the FixMate  Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL JUAN CARLOS RUEDA BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FIXPARSEREXCEPTIONS_H
#define	FIXPARSEREXCEPTIONS_H

#include <exception>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace fprime {

    class InvalidNodeNesting : public exception {
    public:

        InvalidNodeNesting(string parentType, string nestedType) : _parentType(parentType), _nestedType(nestedType) {
        }

        ~InvalidNodeNesting() throw () {
        }

        const string what() throw () {
            stringstream ss;
            ss << "Node nesting rules violated: a " << _parentType << " can't contains a " << _nestedType;
            return ss.str();
        }
    private:
        string _parentType, _nestedType;
    };

    class InvalidFieldSet : public exception {
    public:

        InvalidFieldSet() {
        }

        ~InvalidFieldSet() throw () {
        }

        const string what() throw () {
            return "A root Node can be a Field";
        }
    };

    class ComponentNotFound : public exception {
    public:

        ComponentNotFound(string cName):cmpName(cName) {
        }

        ~ComponentNotFound() throw () {
        }

        const string what() throw () {
            return "Component " + cmpName + " does not exists.";
        }
         private:
            string cmpName;
    };

    class InvalidValueIndex : public exception {
    public:

        InvalidValueIndex() {
        }

        ~InvalidValueIndex() throw () {
        }

        const string what() throw () {
            return "Index greater than 0 is valid for repeating groups only";
        }
    };

    class NullHeader : public exception {
    public:

        NullHeader() {
        }

        ~NullHeader() throw () {
        }

        const string what() throw () {
            return "Header node is null";
        }
    };

    class NullBody : public exception {
    public:

        NullBody() {
        }

        ~NullBody() throw () {
        }

        const string what() throw () {
            return "Body node is null";
        }
    };

    class NullTrailer : public exception {
    public:

        NullTrailer() {
        }

        ~NullTrailer() throw () {
        }

        const string what() throw () {
            return "Trailer node is null";
        }
    };

    class BadConvertion : public exception {
    public:

        BadConvertion() {
        }

        BadConvertion(string _msg) : msg(_msg) {
        }

        ~BadConvertion() throw () {
        }

        const string what() throw () {
            return msg;
        }

    private:
        string msg;
    };

    class NullValue : public exception {
    public:

        NullValue() {
        }

        ~NullValue() throw () {
        }

        const string what() throw () {
            return "Value index does not exists.";
        }
    };

    class InvalidGroup : public exception {
    public:

        InvalidGroup() {
        }

        ~InvalidGroup() throw () {
        }

        const string what() throw () {
            return "Group Node does not exists.";
        }
    };

    class InvalidField : public exception {
    public:

        InvalidField(string msg): errMsg(msg) {
        }

        ~InvalidField() throw () {
        }

        const string what() throw () {
            return errMsg;
        }
    private:
        string errMsg;
    };
    
    class RawMessageException : public exception {
    public:

        RawMessageException() {
        }

        ~RawMessageException() throw () {
        }

        const string what() throw () {
            return "Error getting message from buffer";
        }
    private:
        string errMsg;
    };
}
#endif	/* FIXPARSEREXCEPTIONS_H */

