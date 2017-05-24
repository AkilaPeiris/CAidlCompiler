#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>


class IB : public android::IInterface 
{
    public:
        enum
        {
            TX_CODE_Function2 = android::IBinder::FIRST_CALL_TRANSACTION
        };

        virtual int Function2() = 0;


        DECLARE_META_INTERFACE(B);
};