/* 
 * File:   FixParserExceptions.h
 * Author: DeveloperPrime
 *
 * Created on September 30, 2014, 7:13 AM
 */

#ifndef FIXPARSEREXCEPTIONS_H
#define	FIXPARSEREXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

namespace hfe {

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
}
#endif	/* FIXPARSEREXCEPTIONS_H */

