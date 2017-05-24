
#include "BpAkila.h"

using namespace android;

BpAkila::BpAkila(const sp<IBinder>& impl):
  BpInterface<IAkila>(impl)
{

}

BpAkila::~BpAkila()
{

}

android::sp<IB> BpAkila::iFn1(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn1, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn2(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn2, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn3(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn3, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn4(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn4, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn5(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn5, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn6(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn6, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn7(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn7, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn8(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn8, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn9(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn9, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

android::sp<IB> BpAkila::iFn10(int k, android::sp<IB>& ibba, int i)
{
    Parcel pData, pReply;

    pData.writeInterfaceToken(IAkila::getInterfaceDescriptor());

    pData.writeInt32(k);
    pData.writeStrongBinder(IInterface::asBinder(ibba));
    pData.writeInt32(i);

    remote()->transact(TX_CODE_iFn10, pData, &pReply);

    pReply.readInt32();

    return interface_cast<IB>(pReply.readStrongBinder());
}

