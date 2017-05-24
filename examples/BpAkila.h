#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>

#include "IAkila.h"

/*! This class acts as the client side proxy for BpAkila
*/
class BpAkila : public android::BpInterface<IAkila> 
{
    public:
        /*! Creates an intance of the BpAkila class
        */
        explicit BpAkila(const android::sp<android::IBinder>& impl);
        
        /*! Destroys an instance of the BpAkila class
        */
        virtual ~BpAkila();

        /*! Declaration for client side proxy for the 'iFn1' function 
        */
        virtual android::sp<IB> iFn1(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn2' function 
        */
        virtual android::sp<IB> iFn2(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn3' function 
        */
        virtual android::sp<IB> iFn3(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn4' function 
        */
        virtual android::sp<IB> iFn4(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn5' function 
        */
        virtual android::sp<IB> iFn5(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn6' function 
        */
        virtual android::sp<IB> iFn6(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn7' function 
        */
        virtual android::sp<IB> iFn7(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn8' function 
        */
        virtual android::sp<IB> iFn8(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn9' function 
        */
        virtual android::sp<IB> iFn9(int k, android::sp<IB>& ibba, int i);

        /*! Declaration for client side proxy for the 'iFn10' function 
        */
        virtual android::sp<IB> iFn10(int k, android::sp<IB>& ibba, int i);

};
