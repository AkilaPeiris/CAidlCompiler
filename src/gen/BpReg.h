#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>

#include "IReg.h"

/*! This class acts as the client side proxy for BpReg
*/
class BpReg : public android::BpInterface<IReg> 
{
    public:
        /*! Creates an intance of the BpReg class
        */
        explicit BpReg(const android::sp<android::IBinder>& impl);
        
        /*! Destroys an instance of the BpReg class
        */
        virtual ~BpReg();

        /*! Declaration for client side proxy for the 'i' function 
        */
        virtual int i();

        /*! Declaration for client side proxy for the 'd' function 
        */
        virtual int d();

        /*! Declaration for client side proxy for the 'y' function 
        */
        virtual int y();

        /*! Declaration for client side proxy for the 'r' function 
        */
        virtual int r();

};
