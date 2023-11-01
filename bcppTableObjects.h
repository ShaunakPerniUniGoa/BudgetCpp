#include <vector>
#include <string>
#include <ctime>
#include "bcppTimeFunctionsLib.h"
namespace budgetCppTableObjects
{

    struct accountingRow
    {
        /**
         * @brief Row Structure for Accounting Table Object
         * @brief Contains the SrNo, Item Name and value in floating point
         */
        int serialNumber;
        std::string itemName;
        float valueMoney;
    };

    template <typename RowType>
    class AccountingTableObject
    {
    private:
        std::vector<RowType> tableColumns;

    public:
        AccountingTableObject() {}
        /*
         @brief CURD Functions
        */
        void insertRow(RowType newRow)
        {
            tableColumns.push_back(newRow);
        }
    };

    template <typename RowType>
    class AutomatedAccountingObject
    {
    private:
        RowType accountDetails;
        AccountingTableObject<RowType> &tableRef;
        BudgetCppTimeObjects::timePreoid triggerAfter;
        std::tm lastTrigger;
        bool enabled;

        struct conditonCheck
        {
            int loops;
            bool valid;
        };

        void addNewAccount2RefTable()
        {
            tableRef.insertRow(accountDetails);
        }

        conditonCheck checkTriggerCondition(std::tm currentDate)
        {
            conditonCheck conditonCheckReturn;
            switch (triggerAfter)
            {
            case BudgetCppTimeObjects::DAILY:

                break;

            default:
                conditonCheckReturn.valid = false;
                return conditonCheckReturn;
            }
            conditonCheckReturn.valid = false;
            return conditonCheckReturn;
        }

    public:
        AutomatedAccountingObject(AccountingTableObject<RowType> &table) : tableRef(table)
        {
        }

        void checkConditionAndTrigger(std::tm currentDate)
        {
            if (enabled)
            {
                conditonCheck conditionCheckReturn = checkTriggerCondition(currentDate);
                if (conditionCheckReturn.valid)
                {
                    int loops = conditionCheckReturn.loops;
                    while (loops > 0)
                    {
                        addNewAccount2RefTable();
                        loops--;
                    }
                }
                lastTrigger = BudgetCppTimeFunctions::getCurrentDate();
            }
        }
    };

    class saveDataObject
    {
    private:
    };
}
