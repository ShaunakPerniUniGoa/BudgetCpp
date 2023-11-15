#include "BCPPPackageVectorTable.h"
#include "BCPPPackageTimeLib.h"
#include "BCPPTerminalFormating.h"
#include <string>
#include <iostream>
namespace BCPP_Database_Objects
{
    namespace RowStructures
    {
        struct structAccountingRow
        {
            int serialNumber;
            std::string itemName;
            float valueDebit;
            float valueCredit;
            std::tm date;
        };

        std::string COLUMN_HEADERS = "Sr\t\tItem\t\tDebit\t\tCredit\t\tDate\n";

        auto serialNumberSelector = [](const structAccountingRow &row)
        { return row.serialNumber; };
        auto itemNameSelector = [](const structAccountingRow &row)
        { return row.itemName; };
        auto dateSelector = [](const structAccountingRow &row)
        { return row.date; };
        auto debitSelector = [](const structAccountingRow &row)
        { return row.valueDebit; };
        auto creditSelector = [](const structAccountingRow &row)
        { return row.valueCredit; };

        void printRow(const structAccountingRow &currentRow)
        {
            std::cout << currentRow.serialNumber << "\t\t" << currentRow.itemName << "\t\t" << currentRow.valueDebit << "\t\t" << currentRow.valueCredit << "\t\t" << BCPP_Package_TimeLib::timeDataFormatter::returnFormatedDate(currentRow.date) << std::endl;
        }
    }
}
typedef BCPP_Database_Objects::RowStructures::structAccountingRow AccountingRow;
typedef BCPP_Package_VectorTable::VectorTable<BCPP_Database_Objects::RowStructures::structAccountingRow> AccountingVectorTable;
namespace BCPP_Database_Schema
{
    namespace Tables
    {
        AccountingVectorTable IncomeTable;
        AccountingVectorTable *IncomeTablePtr = &IncomeTable;

        AccountingVectorTable ExpenseTable;
        AccountingVectorTable *ExpenseTablePtr = &ExpenseTable;
    }

    namespace TriggersObjectsContainers
    {

    }
}

namespace BCPP_Interface
{
    namespace dataManipulation
    {
        void insertData(AccountingVectorTable *tableRef, std::string itemName, float valueDebit, float valueCredit)
        {
            auto lastNum = tableRef->returnSize() > 0 ? tableRef->getTail().serialNumber + 1 : 1;
            std::tm currentTime = BCPP_Package_TimeLib::TimeCalculationFunctions::getCurrentDate();
            tableRef->pushRow({lastNum, itemName, valueDebit, valueCredit, currentTime});
        }
    }

    namespace output
    {
        void displayTable(AccountingVectorTable *tableRef)
        {
            std::cout << BCPP_Database_Objects::RowStructures::COLUMN_HEADERS;
            for (const auto &currentRow : tableRef->returnAllRows())
            {
                BCPP_Database_Objects::RowStructures::printRow(currentRow);
            }
        }

        void displayTableRangeByIndex(AccountingVectorTable *tableRef,int indexVal, int offset)
        {
            std::cout<< BCPP_Database_Objects::RowStructures::COLUMN_HEADERS;
            for (const auto &currentRow : tableRef->getRangeByIndex(indexVal,offset))
            {
                BCPP_Database_Objects::RowStructures::printRow(currentRow);
            }
        }

        void displayTableRangeByPk(AccountingVectorTable *tableRef, int pkVal, int offset)
        {
            int derivedIndex = tableRef->findIndexByCustomKey(pkVal,BCPP_Database_Objects::RowStructures::serialNumberSelector);
            displayTableRangeByIndex(tableRef,derivedIndex,offset);
        }

        void displayRowByIndex(AccountingVectorTable *tableRef, int index)
        {
            auto &currentRow = tableRef->returnRow(index);
            BCPP_Database_Objects::RowStructures::printRow(currentRow);
        }

        namespace Account
        {
            float returnBalance(AccountingVectorTable* tableRef)
            {
                float debitTotal = tableRef->sumMember<float>(BCPP_Database_Objects::RowStructures::debitSelector);
                float creditTotal = tableRef->sumMember<float>(BCPP_Database_Objects::RowStructures::creditSelector);
                float balance = creditTotal - debitTotal;
                return balance;
            }
        }

    }
}