#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>


class IReg : public android::IInterface 
{
    public:
        enum
        {
            TX_CODE_i = android::IBinder::FIRST_CALL_TRANSACTION,
            TX_CODE_d,
            TX_CODE_y,
            TX_CODE_r
        };

        virtual int i() = 0;

        virtual int d() = 0;

        virtual int y() = 0;

        virtual int r() = 0;


        DECLARE_META_INTERFACE(Reg);
};