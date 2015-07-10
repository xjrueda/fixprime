/* 
 * File:   StringDataHolder.h
 * Author: Juan_Rueda
 *
 * Created on 6 de mayo de 2015, 04:48 PM
 */

#ifndef STRINGDATAHOLDER_H
#define	STRINGDATAHOLDER_H

#include "DataHolder.h"

namespace fprime {

    class StringDataHolder : public fprime::DataHolder {
    public:
        StringDataHolder();
        StringDataHolder(const StringDataHolder& orig);
        virtual ~StringDataHolder();

        void set(string);
        bool validate();
        string get();
    private:
        int nativeData;
    };
}
#endif	/* STRINGDATAHOLDER_H */

