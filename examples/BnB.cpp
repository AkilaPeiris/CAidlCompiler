#include <binder/Parcel.h>

#include "BnB.h"

using namespace android;

BnB::BnB()
{

}

BnB::~BnB()
{

}

status_t BnB::onTransact(uint32_t iCode, const android::Parcel& pData, android::Parcel* pReply, uint32_t iFlags)
{
    status_t tStatus = NO_ERROR;

    if(pData.checkInterface(this) == false)
    {
        return PERMISSION_DENIED;
    }

    switch(iCode)
    {
        case TX_CODE_Function2:
        {
            int return__val__ = Function2();
        
            pReply->writeInt32(0);

            pReply->writeInt32(return__val__);

            tStatus = NO_ERROR;
        }
        break;

        default:
        {
            tStatus = BBinder::onTransact(iCode, pData, pReply, iFlags);
        }
    }

    return tStatus;
}
