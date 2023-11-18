#include "BCPPDatabase.h"
#include "BCPPPackageTerminalUI.h"
#include "BCPPTerminalFormating.h"
#include <string>

void tablePrint(BankTable *tableRef)
{
    std::vector<BankAccountRow> tableRows = BCPP_Database_Interface::BankTableInterface::returnAllTableRows(tableRef);
    bool Coloralternator = true;
    std::cout<< BCPP_Database_Objects::TableStructues::BankAccount::COLUMN_HEADERS;
    for (const BankAccountRow &row : tableRows)
    {
        std::string rowString = BCPP_Database_Objects::TableStructues::BankAccount::returnRowString(row);
        std::cout<<rowString;
        std::cout << "\n";
    }
}
int main()
{
    BCPP_Database_Interface::AccountsTableInterface::rowCreation::createNewBankTable("Axis Bank");
    auto ptr = BCPP_Database_Interface::AccountsTableInterface::getterFunctions::returnAccountRow(1).tableRef;
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(ptr, "Hello", 0, 0);
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(ptr, "Hello", 10, 0);
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(ptr, "Hello", 10, 0);
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(ptr, "Hello", 10, 0);
    BCPP_Database_Interface::BankTableInterface::pushNewAccountingRow(ptr, "Hello", 10, 0);

    BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("Budget C++ V2.1", terminalFormatingColorcodes::ANSI_BG_WHITE);

    BCPP_Package_TerminalUI::formattedOutputs::fancyOptionsMenu(false,
        {
            {"(i)sert Row",terminalFormatingColorcodes::ANSI_BG_BLUE},
            {"(q)uit", terminalFormatingColorcodes::ANSI_BG_RED}
        }
    );

    BCPP_Package_TerminalUI::formattedOutputs::addMarker(terminalFormatingColorcodes::ANSI_BG_WHITE);
    std::cout<<"Balance  ";
    BCPP_Package_TerminalUI::formattedOutputs::binaryColorThresholdFormatedValue<float>(
        BCPP_Database_Interface::BankTableInterface::returnBalance(ptr),
        terminalFormatingColorcodes::ANSI_BG_GREEN,
        terminalFormatingColorcodes::ANSI_BG_RED,
        0.00
    );
    std::cout<<"\n";
    BCPP_Package_TerminalUI::formattedOutputs::resetMarker();

    tablePrint(ptr);

    BCPP_Package_TerminalUI::formattedPrompts::customPrompt<float>("$:");
}