#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>

#include "IB.h"

class IAkila : public android::IInterface 
{
    public:
        enum
        {
            TX_CODE_iFn1 = android::IBinder::FIRST_CALL_TRANSACTION,
            TX_CODE_iFn2,
            TX_CODE_iFn3,
            TX_CODE_iFn4,
            TX_CODE_iFn5,
            TX_CODE_iFn6,
            TX_CODE_iFn7,
            TX_CODE_iFn8,
            TX_CODE_iFn9,
            TX_CODE_iFn10
        };

        virtual android::sp<IB> iFn1(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn2(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn3(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn4(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn5(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn6(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn7(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn8(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn9(int k, android::sp<IB>& ibba, int i) = 0;

        virtual android::sp<IB> iFn10(int k, android::sp<IB>& ibba, int i) = 0;


        DECLARE_META_INTERFACE(Akila);
};