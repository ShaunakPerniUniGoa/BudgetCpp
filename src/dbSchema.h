#ifndef DBSCHEMA_H
#define DBSCHEMA_H

#include "vectorTables.h"
#include "timeAppliedFuncLib.h"
#include <memory>

namespace BudgetCPP
{
    namespace defines
    {
        typedef float price;
        typedef Backend::Database::Schema::BankStatement::structure::rowBankStatement AccountStatement;
        typedef Package_VectorTable::VectorTable<Backend::Database::Schema::BankStatement::structure::rowBankStatement> AccountStatementTable;
        typedef Backend::Database::Schema::Accounts::structure::rowAccounts BankAccountEntry;
        typedef Package_VectorTable::VectorTable<Backend::Database::Schema::Accounts::structure::rowAccounts> BankAccountsTable;
    }
    namespace Backend
    {
        namespace Database
        {
            namespace Schema
            {
                using namespace defines;
                namespace BankStatement
                {
                    namespace structure
                    {
                        struct rowBankStatement
                        {
                            int serialNumber;
                            std::string payee;
                            price valueDebit;
                            price valueCredit;
                            std::tm date;
                        };

                    }
                    namespace selectors
                    {
                        using namespace structure;
                        auto selectionSerialNumber = [](const rowBankStatement &row){ return row.serialNumber; };
                        auto selectionPayee = [](const rowBankStatement &row){ return row.payee; };
                        auto selectionValueDebit = [](const rowBankStatement &row){ return row.valueDebit; };
                        auto selectionValueCredit = [](const rowBankStatement &row){ return row.valueCredit; };
                        auto selectionDate = [](const rowBankStatement &row){ return row.date; };
                    }
                    namespace printFormatter
                    {
                        using namespace structure;
                        std::string HeaderString = "Serial Number\tPayee\t\tValue Debit\tValue Credit\tDate\n";

                        std::string returnDataRow(const rowBankStatement &inputRow)
                        {
                            std::ostringstream stringStream;
                            stringStream << inputRow.serialNumber << "\t\t"
                                     << inputRow.payee << "\t\t"
                                     << inputRow.valueDebit << "\t\t"
                                     << inputRow.valueCredit << "\t\t"
                                     << inputRow.date.tm_year + 1900 << "-" << inputRow.date.tm_mon + 1 << "-" << inputRow.date.tm_mday;
                            return stringStream.str();
                        }
                    }
                }
                namespace Accounts
                {
                    namespace structure
                    {
                        struct rowAccounts
                        {
                            int serialNumber;
                            std::string accountName;
                            Package_VectorTable::VectorTable<BankStatement::structure::rowBankStatement> *bankStatementTableRef;
                            price balance;
                        };

                    }
                    namespace selectors
                    {
                        using namespace structure;
                        auto selectorSerialNumber = [](const rowAccounts &row){ return row.serialNumber; };
                        auto selectorAccountName = [](const rowAccounts &row){ return row.accountName; };
                        auto selectorBalance = [](const rowAccounts &row){ return row.balance; };
                        auto selectorBankStatementTableRef = [](const rowAccounts &row){ return row.bankStatementTableRef; };

                        template <typename DebitSelectorType, typename CreditSelectorType>
                        void calculateBalance(DebitSelectorType debitSelector, CreditSelectorType creditSelector)
                        {
                            const auto debit = tableRef->template sumMember<float>(debitSelector);
                            const auto credit = tableRef->template sumMember<float>(creditSelector);
                            balance = credit - debit;
                        }

                        }
                    namespace printFormatter
                    {
                        using namespace structure;
                        std::string HeaderString = "Serial Number\tPayee\t\tValue Debit\tValue Credit\tDate\n";

                        std::string returnDataRow(const BankStatement::structure::rowBankStatement &inputRow)
                        {
                            std::ostringstream stringStream;
                            stringStream << inputRow.serialNumber << "\t\t"
                                     << inputRow.payee << "\t\t"
                                     << inputRow.valueDebit << "\t\t"
                                     << inputRow.valueCredit << "\t\t"
                                     << inputRow.date.tm_year + 1900 << "-" << inputRow.date.tm_mon + 1 << "-" << inputRow.date.tm_mday;
                            return stringStream.str();
                        }
                    }
                }
            }
            namespace Tables
            {
                defines::BankAccountsTable MyBankAccountsTable;
                defines::BankAccountsTable* ptrMyBankAccountsTable = &MyBankAccountsTable;
                std::unique_ptr<defines::AccountStatementTable> ptrAccountStatementTable;
            }
            namespace Interface
            {
                void createNewBankStatementTable()
                {
                    Tables::ptrAccountStatementTable = std::make_unique<Package_VectorTable::VectorTable<defines::AccountStatement>>();
                }

            }
        }
    }
}

#endif // DBSCHEMA_H