#ifndef DBSCHEMA_H
#define DBSCHEMA_H

#include "../include/VectorTables/src/vectorTables.h"
#include "../include/TimeAppliedFuncLib/src/timeAppliedFuncLib.h"
#include <memory>

namespace BudgetCPP
{
    namespace defines
    {
        typedef float price;
    }
    namespace Backend
    {
        namespace Database
        {
            namespace Schema
            {
                using namespace defines;
                namespace TransactionRecord
                {
                    namespace structure
                    {
                        struct rowTransactionRecord
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
                        auto selectionSerialNumber = [](const rowTransactionRecord &row){ return row.serialNumber; };
                        auto selectionPayee = [](const rowTransactionRecord &row){ return row.payee; };
                        auto selectionValueDebit = [](const rowTransactionRecord &row){ return row.valueDebit; };
                        auto selectionValueCredit = [](const rowTransactionRecord &row){ return row.valueCredit; };
                        auto selectionDate = [](const rowTransactionRecord &row){ return row.date; };
                    }
                    namespace printFormatter
                    {
                        using namespace structure;
                        std::string HeaderString = "Serial Number\tPayee\t\tValue Debit\tValue Credit\tDate\n";

                        std::string returnDataRow(const rowTransactionRecord &inputRow)
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
                namespace AccountRecord
                {
                    namespace structure
                    {
                        struct rowAccountRecord
                        {
                            int serialNumber;
                            std::string accountName;
                            Package_VectorTable::VectorTable<TransactionRecord::structure::rowTransactionRecord> *TransactionRecordTableRef;
                            price balance;
                        };

                    }
                    namespace selectors
                    {
                        using namespace structure;
                        auto selectorSerialNumber = [](const rowAccountRecord &row){ return row.serialNumber; };
                        auto selectorAccountName = [](const rowAccountRecord &row){ return row.accountName; };
                        auto selectorBalance = [](const rowAccountRecord &row){ return row.balance; };
                        auto selectorBankStatementTableRef = [](const rowAccountRecord &row){ return row.TransactionRecordTableRef; };
                    }
                    namespace printFormatter
                    {
                        using namespace structure;
                        std::string HeaderString = "Serial Number\tPayee\t\tValue Debit\tValue Credit\tDate\n";

                        std::string returnDataRow(const TransactionRecord::structure::rowTransactionRecord &inputRow)
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
                Package_VectorTable::VectorTable<Schema::AccountRecord::structure::rowAccountRecord> TableOfBankAccounts;
                Package_VectorTable::VectorTable<Schema::AccountRecord::structure::rowAccountRecord>* TableOfBankAccountsRef = &TableOfBankAccounts;
            }
            namespace Inits
            {
                Package_VectorTable::VectorTable<Schema::TransactionRecord::structure::rowTransactionRecord> newTransactionRecordTable;
                Schema::TransactionRecord::structure::rowTransactionRecord newTransactionRecord = {1, "Initial Transaction", 0, 100, std::tm{}};
                Schema::AccountRecord::structure::rowAccountRecord newAccountRecord = {1, "New Account", &newTransactionRecordTable, 0};
            }
            namespace Interface
            {

            }
        }
    }
}

#endif // DBSCHEMA_H