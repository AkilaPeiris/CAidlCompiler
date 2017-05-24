#include <binder/Parcel.h>

#include "BnReg.h"

using namespace android;

BnReg::BnReg()
{

}

BnReg::~BnReg()
{

}

status_t BnReg::onTransact(uint32_t iCode, const android::Parcel& pData, android::Parcel* pReply, uint32_t iFlags)
{
    status_t tStatus = NO_ERROR;

    if(pData.checkInterface(this) == false)
    {
        return PERMISSION_DENIED;
    }

    switch(iCode)
    {
        case TX_CODE_i:
        {
            int return__val__ = i();
        
            pReply->writeInt32(0);

            pReply->writeInt32(return__val__);

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_d:
        {
            int return__val__ = d();
        
            pReply->writeInt32(0);

            pReply->writeInt32(return__val__);

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_y:
        {
            int return__val__ = y();
        
            pReply->writeInt32(0);

            pReply->writeInt32(return__val__);

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_r:
        {
            int return__val__ = r();
        
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
