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

            void TriggerFunction(std::function<void()> function)
            {
                target->function();
            };

            void checkAndActivateTrigger(){};
        };

        template <typename Object, typename Data, typename TriggerFunctionDataType, typename... passArgs>
        class DataTrigger : protected Trigger<Object>
        {
        protected:
            Data data;

        public:
            void TriggerFunction(std::function<TriggerFunctionDataType(passArgs...)> function)
            {
                Trigger<Object>::target->function(data);
            };
        };

        template <typename Object, typename Data, typename TriggerFunctionDataType, typename... passArgs>
        class TimerDataTrigger : protected DataTrigger<Object, Data, TriggerFunctionDataType, passArgs...>
        {
            using DataTrigger<Object, Data, TriggerFunctionDataType, passArgs...>::TriggerFunction;
            private:
            BCPP_Package_TimeLib::TimeObjects::TimePreoids repeatAfter;
            
        };

    };
}