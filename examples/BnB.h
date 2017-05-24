#pragma once

#include "IB.h"

/*! This class acts as the implementation side stub for B
*/
class BnB : public android::BnInterface<IB> 
{
    public:
        /*! Creates an intance of the BnB class
        */
        BnB();
        
        /*! Destroys an instance of the BnB class
        */
        virtual ~BnB();

        /*! Transaction entry point for the application
        */
        virtual android::status_t onTransact(uint32_t iCode, const android::Parcel& pData,
                 android::Parcel* pReply, uint32_t iFlags = 0);

};
