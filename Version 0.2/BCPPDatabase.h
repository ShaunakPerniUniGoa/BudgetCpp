#include "BCPPPackageVectorTable.h"
#include "BCPPPackageTimeLib.h"
#include "BCPPTerminalFormating.h"
#include <string>
#include <iostream>
#include <memory>
namespace BCPP_Database_Objects
{
    namespace TableStructues
    {
        namespace BankAccount
        {
            struct rowBankAccount
            {
                int serialNumber;
                std::string payee;
                float valueDebit;
                float valueCredit;
                std::tm date;
            };

            auto serialNumberSelector = [](const rowBankAccount &row)
            { return row.serialNumber; };

            auto valueDebitSelector = [](const rowBankAccount &row)
            { return row.valueDebit; };

            auto valueCreditSelector = [](const rowBankAccount &row)
            { return row.valueCredit; };

            std::string COLUMN_HEADERS = "Sr\t\tItem\t\tDebit\t\tCredit\t\tDate\n";

            std::string returnRowString(const rowBankAccount &currentRow)
            {
                std::ostringstream oss;
                oss << currentRow.serialNumber << "\t\t"
                    << currentRow.payee << "\t\t"
                    << currentRow.valueDebit << "\t\t"
                    << currentRow.valueCredit << "\t\t"
                    << BCPP_Package_TimeLib::timeDataFormatter::returnFormatedDate(currentRow.date);

                return oss.str();
            }
        }
        namespace Accounts
        {
            template <typename rowStruct>
            struct RowAccounts
            {
                int serialNumber;
                std::string accoutnName;
                BCPP_Package_VectorTable::VectorTable<rowStruct> *tableRef;
                float balance;

                template <typename DebitSelector, typename CreditSelector>
                void setBalance(DebitSelector debitSelector, CreditSelector creditSelector)
                {
                    auto debit = tableRef->template sumMember<float>(debitSelector);
                    auto credit = tableRef->template sumMember<float>(creditSelector);
                    this->balance = credit - debit;
                }
            };

            template <typename rowStruct>
            void printRow(const RowAccounts<rowStruct> &row)
            {
                std::cout << row.serialNumber << terminalFormatingMisc::spacer << row.accoutnName << terminalFormatingMisc::spacer << row.balance;
            }
        }
    }
}

typedef BCPP_Database_Objects::TableStructues::BankAccount::rowBankAccount BankAccountRow;
typedef BCPP_Package_VectorTable::VectorTable<BankAccountRow> BankTable;

typedef BCPP_Database_Objects::TableStructues::Accounts::RowAccounts<BankAccountRow> AccountRow;
typedef BCPP_Package_VectorTable::VectorTable<AccountRow> BankAccountsTable;

std::unique_ptr<BCPP_Package_VectorTable::VectorTable<BankAccountRow>> tablePtr;

namespace BCPP_Database_Schema
{
    namespace Tables
    {
        BankAccountsTable AccountsTable;
        BankAccountsTable *AccountsTablePtr = &AccountsTable;
    }

}

// DEPRICIATED
/*namespace BCPP_Interface
{
    namespace dataManipulation
    {
        void insertData(AccountingVectorTable *tableRef, std::string itemName, float valueDebit, float valueCredit)
        {
            auto lastNum = tableRef->returnSize() > 0 ? tableRef->getTail().serialNumber + 1 : 1;
            std::tm currentTime = BCPP_Package_TimeLib::TimeCalculationFunctions::getCurrentDate();
            tableRef->pushRow({lastNum, itemName, valueDebit, valueCredit, currentTime});
        }

        void updateData(AccountingVectorTable * tableRef, int KeyVal)
        {
            int serialNum = tableRef->returnRow(KeyVal-1).serialNumber;

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
}*/

namespace BCPP_Database_Interface
{
    namespace AccountsTableInterface
    {
        namespace rowCreation
        {
            void createNewBankTable(std::string accountName)
            {
                tablePtr = std::make_unique<BCPP_Package_VectorTable::VectorTable<BankAccountRow>>();
                AccountRow newRow = {1, accountName, tablePtr.get(), 0};
                newRow.setBalance(
                    BCPP_Database_Objects::TableStructues::BankAccount::valueDebitSelector,
                    BCPP_Database_Objects::TableStructues::BankAccount::valueCreditSelector);
                BCPP_Database_Schema::Tables::AccountsTable.pushRow(newRow);
            }
        }

        namespace getterFunctions
        {
            auto returnAccountRow(int indexVal)
            {
                return BCPP_Database_Schema::Tables::AccountsTable.returnRow(indexVal);
            }
        }
    }
    namespace BankTableInterface
    {
        void pushNewAccountingRow(BankTable *tableRef, std::string payee, float debit, float credit)
        {
            int lastSerial = tableRef->returnSize();
            tableRef->pushRow({lastSerial, payee, debit, credit, BCPP_Package_TimeLib::TimeCalculationFunctions::getCurrentDate()});
        }

        auto returnAllTableRows(BankTable *tableRef)
        {
            return tableRef->returnAllRows();
        }

        float returnBalance(BankTable *tableRef)
        {
            float debit = tableRef->sumMember<float>(BCPP_Database_Objects::TableStructues::BankAccount::valueDebitSelector);
            float credit = tableRef->sumMember<float>(BCPP_Database_Objects::TableStructues::BankAccount::valueCreditSelector);
            float Balance = credit - debit;
            return Balance;
        }
    }
}