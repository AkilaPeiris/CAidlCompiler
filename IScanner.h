#pragma once

#include <binder/IInterface.h>
#include <binder/IBinder.h>

#include <string>

class IScanner : public android::IInterface 
{
    public:
        enum
        {
            TX_CODE_getNumberofConnectionObjects = android::IBinder::FIRST_CALL_TRANSACTION,
            TX_CODE_getNumberofConnectionObjects2,
            TX_CODE_getNumberofConnectionObjects3
        };

        virtual void getNumberofConnectionObjects(int i, std::string s) = 0;

        virtual std::string getNumberofConnectionObjects2() = 0;

        virtual int getNumberofConnectionObjects3() = 0;


        DECLARE_META_INTERFACE(Scanner);
};