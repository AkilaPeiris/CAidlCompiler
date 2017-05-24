#pragma once

#include "IAkila.h"

/*! This class acts as the implementation side stub for Akila
*/
class BnAkila : public android::BnInterface<IAkila> 
{
    public:
        /*! Creates an intance of the BnAkila class
        */
        BnAkila();
        
        /*! Destroys an instance of the BnAkila class
        */
        virtual ~BnAkila();

        /*! Transaction entry point for the application
        */
        virtual android::status_t onTransact(uint32_t iCode, const android::Parcel& pData,
                 android::Parcel* pReply, uint32_t iFlags = 0);

};
