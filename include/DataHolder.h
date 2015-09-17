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

#ifndef DATATYPE_H
#define	DATATYPE_H

#include "DataHolderFactorySettings.h"
#include <string>
#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;

namespace fprime {

    class DataHolder {
    public:

        DataHolder() {
        }

        virtual ~DataHolder() {
        }

        typedef shared_ptr<DataHolder> DataTypePtr;

        virtual void set(const string data) { baseData = data;}
        virtual const string get() {return baseData;}
        
        virtual bool validate() = 0;
        

        virtual int toInt() {
            try {
                return boost::lexical_cast<int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual unsigned int toUsignedInt() {
            try {
                return boost::lexical_cast<unsigned int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual float tofloat() {
            try {
                return boost::lexical_cast<float>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual double toDouble() {
            try {
                return boost::lexical_cast<double>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long toLong() {
            try {
                return boost::lexical_cast<long>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long int toLongInt() {
            try {
                return boost::lexical_cast<long int>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual long double toLongDouble() {
            try {
                return boost::lexical_cast<long double>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }

        virtual short toShort() {
            try {
                return boost::lexical_cast<short>(baseData);
            } catch(exception& e) {
                throw runtime_error("Invalid data type conversion");
            }
        }
    protected:
        string baseData;
    };
}
#endif	/* DATATYPE_H */

