#include <binder/Parcel.h>

#include "BnAkila.h"

using namespace android;

BnAkila::BnAkila()
{

}

BnAkila::~BnAkila()
{

}

status_t BnAkila::onTransact(uint32_t iCode, const android::Parcel& pData, android::Parcel* pReply, uint32_t iFlags)
{
    status_t tStatus = NO_ERROR;

    if(pData.checkInterface(this) == false)
    {
        return PERMISSION_DENIED;
    }

    switch(iCode)
    {
        case TX_CODE_iFn1:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn1(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn2:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn2(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn3:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn3(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn4:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn4(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn5:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn5(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn6:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn6(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn7:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn7(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn8:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn8(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn9:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn9(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

            tStatus = NO_ERROR;
        }
        break;

        case TX_CODE_iFn10:
        {
            int user_def_var__k = pData.readInt32();
            sp<IB> user_def_var__ibba = interface_cast<IB>(pData.readStrongBinder());
            int user_def_var__i = pData.readInt32();

            sp<IB> return__val__ = iFn10(user_def_var__k, user_def_var__ibba, user_def_var__i);
        
            pReply->writeInt32(0);

            pReply->writeStrongBinder(IInterface::asBinder(return__val__));

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
