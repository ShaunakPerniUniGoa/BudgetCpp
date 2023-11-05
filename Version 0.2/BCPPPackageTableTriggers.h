#include "BCPPPackageTimeLib.h"
#include <functional>

namespace BCPP_Package_Trigger
{
    namespace Class
    {
        template <typename Object>
        class Trigger
        {
        protected:
            Object *target;

        public:
            Trigger(Object &ObjectRef) : target(&ObjectRef)
            {
            }

            void checkAndActiveTrigger(){
            };
        };

        template<typename Object, typename Data>
        class DataTrigger : protected Trigger<Object>
        {
            
        };


    };
}