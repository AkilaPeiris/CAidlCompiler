#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>

class IBTScannerService : public android::IInterface 
{
    public:
        enum
        {
            INT_getNumberofConnectionObjects = android::IBinder::FIRST_CALL_TRANSACTION,
            INT_getNumberofConnectionObjects2,
            INT_getNumberofConnectionObjects3
        };

        virtual int getNumberofConnectionObjects(int i) = 0;

        virtual int getNumberofConnectionObjects2() = 0;

        virtual int getNumberofConnectionObjects3() = 0;


        DECLARE_META_INTERFACE(BTScannerService);
}