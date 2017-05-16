#include "BpScanner.h"

BpScanner::BpScanner(const sp<IBinder>& impl):
  BpInterface<IScanner>(impl)
{

}

BpScanner::~BpScanner()
{

}

void BpScanner::getNumberofConnectionObjects(int i, std::string s)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IScanner::getInterfaceDescriptor());

    pData.writeInt32(i);
    String16 __s(s); pData->writeString16(s);

    remote()->transact(TX_CODE_getNumberofConnectionObjects, pData, &pReply);

    pReply.readInt32();
}

std::string BpScanner::getNumberofConnectionObjects2()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IScanner::getInterfaceDescriptor());

    remote()->transact(TX_CODE_getNumberofConnectionObjects2, pData, &pReply);

    pReply.readInt32();

    return String8(pReply.readString16()).string();
}

int BpScanner::getNumberofConnectionObjects3()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IScanner::getInterfaceDescriptor());

    remote()->transact(TX_CODE_getNumberofConnectionObjects3, pData, &pReply);

    pReply.readInt32();

    return pReply.readInt32();
}

