/* 
 * File:   UIntDataHolder.h
 * Author: Juan_Rueda
 *
 * Created on 4 de mayo de 2015, 04:51 PM
 */

#ifndef UINTDATAHOLDER_H
#define	UINTDATAHOLDER_H

#include "DataHolder.h"

namespace hfe {

    class UIntDataHolder: public DataHolder {
    public:
        UIntDataHolder();
        UIntDataHolder(const UIntDataHolder& orig);
        virtual ~UIntDataHolder();
        void set(string);
        bool validate();
        string get();
    private:
        unsigned int nativeData;
    };
}
#endif	/* UINTDATAHOLDER_H */

