#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>

#include "IScanner.h"

/*! This class acts as the client side proxy for BpScanner
*/
class BpScanner : public android::BpInterface<IScanner> 
{
    public:
        /*! Creates an intance of the BpScanner class
        */
        explicit BpScanner(const android sp::<android::IBinder>& impl);
        */
        /*! Destroys an instance of the BpScanner class
        */
        virtual ~BpScanner();

        /*! Declaration for client side proxy for the 'getNumberofConnectionObjects' function 
        */
        virtual void getNumberofConnectionObjects(int i, std::string s);

        /*! Declaration for client side proxy for the 'getNumberofConnectionObjects2' function 
        */
        virtual std::string getNumberofConnectionObjects2();

        /*! Declaration for client side proxy for the 'getNumberofConnectionObjects3' function 
        */
        virtual int getNumberofConnectionObjects3();

};