
#include "BpB.h"

using namespace android;

BpB::BpB(const sp<IBinder>& impl):
  BpInterface<IB>(impl)
{

}

BpB::~BpB()
{

}

int BpB::Function2()
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IB::getInterfaceDescriptor());

    remote()->transact(TX_CODE_Function2, pData, &pReply, IBinder::FLAG_ONEWAY);

    pReply.readInt32();

    return pReply.readInt32();
}

