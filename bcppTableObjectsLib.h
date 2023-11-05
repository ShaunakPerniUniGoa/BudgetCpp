#include <vector>
#include <string>
#include <ctime>
#include "bcppTimeFunctionsLib.h"
#include <iostream>
#include <numeric>

namespace budgetCppTableObjects
{
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

        RowType &getRow(int index)
        {
            if (index >= 0 && index < tableColumns.size())
            {
                return tableColumns[index];
            }
            throw std::out_of_range("Index out of range");
        }

        void updateRow(int index, const RowType &updatedRow)
        {
            if (index >= 0 && index < tableColumns.size())
            {
                tableColumns[index] = updatedRow;
            }
            else
            {
                throw std::out_of_range("Index out of range");
            }
        }

        void deleteRow(int index)
        {
            if (index >= 0 && index < tableColumns.size())
            {
                tableColumns.erase(tableColumns.begin() + index);
            }
            else
            {
                throw std::out_of_range("Index out of range");
            }
        }

        int getRowCount()
        {
            return tableColumns.size();
        }

        template <typename MemberType, typename MemberSelector>
        MemberType sumMembers(MemberSelector selector) const
        {
            MemberType total = MemberType{};
            for (const RowType &row : tableColumns)
            {
                total += selector(row);
            }
            return total;
        }

        const std::vector<RowType> &getAllRows() const
        {
            return tableColumns;
        }

        RowType getTail() const
        {
            if (!tableColumns.empty())
            {
                return tableColumns.back();
            }
            throw std::logic_error("Table is empty, cannot retrieve the tail.");
        }

        RowType getHead() const
        {
            if (!tableColumns.empty())
            {
                return tableColumns.front();
            }
            throw std::logic_error("Table is empty, cannot retrieve the head.");
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

            void isValid()
            {
                valid = (loops > 0);
            }
        };

        void addNewAccount2RefTable()
        {
            tableRef.insertRow(accountDetails);
        }

        conditonCheck checkTriggerCondition()
        {
            std::tm currentDate = BudgetCppTimeFunctions::getCurrentDate();
            conditonCheck conditonCheckReturn;
            switch (triggerAfter)
            {
            case BudgetCppTimeObjects::DAILY:
                conditonCheckReturn.loops = BudgetCppTimeFunctions::daysDifference(lastTrigger, currentDate);
                conditonCheckReturn.isValid();
                break;

            case BudgetCppTimeObjects::WEEKLY:
                conditonCheckReturn.loops = BudgetCppTimeFunctions::weekDifference(lastTrigger, currentDate);
                conditonCheckReturn.isValid();
                break;

            case BudgetCppTimeObjects::MONTHLY:
                conditonCheckReturn.loops = BudgetCppTimeFunctions::monthDifference(lastTrigger, currentDate);
                conditonCheckReturn.isValid();
                break;

            case BudgetCppTimeObjects::ANNUALLY:
                conditonCheckReturn.loops = BudgetCppTimeFunctions::yearDifference(lastTrigger, currentDate);
                conditonCheckReturn.isValid();
                break;

            default:
                conditonCheckReturn.valid = false;
                return conditonCheckReturn;
            }
            conditonCheckReturn.valid = false;
            return conditonCheckReturn;
        }

    public:
        AutomatedAccountingObject(AccountingTableObject<RowType> &table) : tableRef(table), enabled(true)
        {
        }

        void checkConditionAndTrigger()
        {
            if (enabled)
            {
                conditonCheck conditionCheckReturn = checkTriggerCondition();
                if (conditionCheckReturn.valid)
                {
                    for (int rowOperationLoops = conditionCheckReturn.loops; rowOperationLoops > 0; rowOperationLoops--)
                    {
                        addNewAccount2RefTable();
                    }
                    lastTrigger = BudgetCppTimeFunctions::getCurrentDate();
                }
            }
        }
    };

    class saveDataObject
    {
    private:
    };
}
