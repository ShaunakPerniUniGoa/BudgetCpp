#include "BCPPDatabase.h"
#include "BCPPPackageTerminalUI.h"
#include "BCPPTerminalFormating.h"
#include <tuple>

void bankTablePrint(BankTable *tableRef)
{
    BCPP_Package_TerminalUI::formattedOutputs::highlightText("Balance  ", terminalFormatingColorcodes::ANSI_BG_WHITE);
    std::cout << "  ";
    BCPP_Package_TerminalUI::formattedOutputs::binaryColorThresholdFormatedValue<float>(
        BCPP_Database_Interface::BankTableInterface::returnBalance(tableRef),
        terminalFormatingColorcodes::ANSI_BG_GREEN,
        terminalFormatingColorcodes::ANSI_BG_RED,
        0);
    std::cout << "\n";
    std::vector<BankAccountRow> tableRows = BCPP_Database_Interface::BankTableInterface::returnAllTableRows(tableRef);
    std::cout << BCPP_Database_Objects::TableStructues::BankAccount::COLUMN_HEADERS;
    for (const BankAccountRow &row : tableRows)
    {
        std::string rowString = BCPP_Database_Objects::TableStructues::BankAccount::returnRowString(row);
        std::cout << rowString;
        std::cout << "\n";
    }
}

void accountTablePrint()
{
    std::cout<<BCPP_Database_Objects::TableStructues::Accounts::RowHeaders<<"\n";
    for (auto &row : BCPP_Database_Interface::AccountsTableInterface::getterFunctions::returnAllAccounts())
    {
        std::cout << row.serialNumber << "\t\t" << row.accoutnName << "\t\t";
        BCPP_Package_TerminalUI::formattedOutputs::binaryColorThresholdFormatedValue<float>(
            BCPP_Database_Interface::BankTableInterface::returnBalance(row.tableRef),
            terminalFormatingColorcodes::ANSI_BG_GREEN,
            terminalFormatingColorcodes::ANSI_BG_RED,
            0);
        std::cout << "\n";
    }
}
void inputNewBankTableRow(BankTable *tableRef)
{
    std::string payee;
    float debit, credit;
    payee = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<std::string>("&:", "Enter Payee Name");
    debit = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<float>("$:", "Enter Debit Amount");
    credit = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<float>("$:", "Enter Credit Amount");
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(tableRef, payee, debit, credit);
}

void inputAccount()
{
    std::string AccountName = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<std::string>("Enter Acccount Name%:");
    BCPP_Database_Interface::AccountsTableInterface::rowCreation::createNewBankTable(AccountName);
}

int main()
{
    BCPP_Database_Interface::AccountsTableInterface::rowCreation::createNewBankTable("AXIS BANK");
    auto currentbankTablePtr = BCPP_Database_Interface::AccountsTableInterface::getterFunctions::returnAccountRow(0);
    bool sessionSwitch = true;
    char optionSelector;
    bool editorSessionSwitch = false;
    while (sessionSwitch)
    {
        BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("BudgetCPP  V2.0   ", terminalFormatingColorcodes::ANSI_BG_WHITE);
        BCPP_Package_TerminalUI::formattedOutputs::fancyOptionsMenu(
            false,
            {//{"(A)dd Account", terminalFormatingColorcodes::ANSI_BG_BLUE},
             {"(T)able\t", terminalFormatingColorcodes::ANSI_BG_GREEN},
             {"(Q)uit", terminalFormatingColorcodes::ANSI_BG_RED}});
        BCPP_Package_TerminalUI::formattedOutputs::highlightText("Accounts Summary",terminalFormatingColorcodes::ANSI_BG_WHITE);
        std::cout<<"\n";
        accountTablePrint();
        optionSelector = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<char>("$:");
        BCPP_Package_TerminalUI::formattedOutputs::resetMarker();
        switch(optionSelector)
        {
            case 'Q':
                sessionSwitch = false;
                break;
            case 'T':
                editorSessionSwitch = true;
                while(editorSessionSwitch)
                {
                    BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("Table Editor   ",terminalFormatingColorcodes::ANSI_BG_GREEN);
                    BCPP_Package_TerminalUI::formattedOutputs::fancyOptionsMenu
                    (
                        false,
                        {
                            {"(i)nsert New Transaction", terminalFormatingColorcodes::ANSI_BG_BLUE},
                            //{"(s)witch Account", terminalFormatingColorcodes::ANSI_BG_MAGENTA},
                            {"(q)uit", terminalFormatingColorcodes::ANSI_BG_RED}
                        }
                    );
                    BCPP_Package_TerminalUI::formattedOutputs::highlightText(currentbankTablePtr.accoutnName,terminalFormatingColorcodes::ANSI_WHITE);
                    std::cout<<"\n";
                    bankTablePrint(currentbankTablePtr.tableRef);
                    optionSelector = BCPP_Package_TerminalUI::formattedPrompts::customPrompt<char>("$:");
                    switch (optionSelector)
                    {
                    case 'i':
                        inputNewBankTableRow(currentbankTablePtr.tableRef);
                        break;
                    
                    default:
                        editorSessionSwitch = false;
                        break;
                    }
                    
                }
                break;
            case 'A':
                inputAccount();
                break;
            default:
                BCPP_Package_TerminalUI::formattedOutputs::resetMarker();
                break;
        }
    }
}