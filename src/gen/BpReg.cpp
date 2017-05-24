
#include "BpReg.h"

using namespace android;

BpReg::BpReg(const sp<IBinder>& impl):
  BpInterface<IReg>(impl)
{

}

BpReg::~BpReg()
{

}

int BpReg::i()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IReg::getInterfaceDescriptor());

    remote()->transact(TX_CODE_i, pData, &pReply);

    pReply.readInt32();

    return pReply.readInt32();
}

int BpReg::d()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IReg::getInterfaceDescriptor());

    remote()->transact(TX_CODE_d, pData, &pReply);

    pReply.readInt32();

    return pReply.readInt32();
}

int BpReg::y()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IReg::getInterfaceDescriptor());

    remote()->transact(TX_CODE_y, pData, &pReply);

    pReply.readInt32();

    return pReply.readInt32();
}

int BpReg::r()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IReg::getInterfaceDescriptor());

    remote()->transact(TX_CODE_r, pData, &pReply);

    pReply.readInt32();

    return pReply.readInt32();
}

