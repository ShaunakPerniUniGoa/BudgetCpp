#include <vector>
#include <string>
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
    };

    template <typename RowType>
    class AutomatedAccountingObject
    {
    private:
        RowType accountDetails;
        AccountingTableObject<RowType> &TableRef;

    public:
        AutomatedAccountingObject(AccountingTableObject<RowType> &table) : TableRef(table)
        {
        }
    };
}