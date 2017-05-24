#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>

#include "IB.h"

/*! This class acts as the client side proxy for BpB
*/
class BpB : public android::BpInterface<IB> 
{
    public:
        /*! Creates an intance of the BpB class
        */
        explicit BpB(const android::sp<android::IBinder>& impl);
        
        /*! Destroys an instance of the BpB class
        */
        virtual ~BpB();

        /*! Declaration for client side proxy for the 'Function2' function 
        */
        virtual int Function2();

};
