#include "BCPPPackageTimeLib.h"
#include <functional>

namespace BCPP_Package_Trigger
{
    namespace Class
    {
        template <typename Object>
        class Trigger
        {
        private:
            Object *target;

        public:
            Trigger(Object &ObjectRef) : target(&ObjectRef)
            {
            }

            void checkAndActiveTrigger(){
            };
        };

        template<typename Object, typename Data>
        class DataCarryTrigger : private Trigger<Object>
        {

        };


    };
}