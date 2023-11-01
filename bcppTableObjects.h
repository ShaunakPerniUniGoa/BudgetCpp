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
        BudgetCppTimeObjects::timePreoid automateAfter;
        std::tm lastTrigger;

        bool enabled;

        void addNewAccount2RefTable()
        {
            tableRef.insertRow(accountDetails);
        }

        bool checkTriggerCondition()
        {
            return true;
        }

    public:
        AutomatedAccountingObject(AccountingTableObject<RowType> &table) : tableRef(table)
        {
        }

        void checkConditionAndTrigger()
        {
            bool conditionReturn = checkTriggerCondition();
            conditionReturn ? addNewAccount2RefTable() : false;
            lastTrigger = BudgetCppTimeFunctions::getCurrentDate();
        }
    };

    class saveDataObject
    {
    private:
    };
}
