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

            const std::string RowHeaders = "Sr.\t\tName\t\t\tBalance";

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

            auto returnAllAccounts()
            {
                return BCPP_Database_Schema::Tables::AccountsTablePtr->returnAllRows();
            }

        }
    }
    namespace BankTableInterface
    {
        void pushNewAccountingRow(BankTable *tableRef, std::string payee, float debit, float credit)
        {
            int lastSerial = tableRef->returnSize();
            std::tm currentTime = BCPP_Package_TimeLib::TimeCalculationFunctions::getCurrentDate();
            tableRef->pushRow({lastSerial, payee, debit, credit, currentTime});
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