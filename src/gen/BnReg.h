#pragma once

#include "IReg.h"

/*! This class acts as the implementation side stub for Reg
*/
class BnReg : public android::BnInterface<IReg> 
{
    public:
        /*! Creates an intance of the BnReg class
        */
        BnReg();
        
        /*! Destroys an instance of the BnReg class
        */
        virtual ~BnReg();

        /*! Transaction entry point for the application
        */
        virtual android::status_t onTransact(uint32_t iCode, const android::Parcel& pData,
                 android::Parcel* pReply, uint32_t iFlags = 0);

};
