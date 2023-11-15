#include "BCPPDatabase.h"
#include "BCPPPackageTerminalUI.h"
#include "BCPPTerminalFormating.h"
#include <string>
int main()
{
    bool sessionSwitch = true;
    bool menusession = false;
    char menuSelection = 't';
    std::vector<std::string> tableTabs = {"Income", "Expense"};
    std::vector<std::string> menuOptions = {"(t)able View", "(q)uit"};
    std::vector<std::string> tableMenuOptions = {"(q)uit", "(i)nsert row", "(d)elete row", "(s)wap rows", "(S)witch Table"};
    /*
        q = quit
        t = tableView

    */
    char optionSelection = 'a';
    /*
        a =
    */
    AccountingVectorTable **currentPointer = &BCPP_Database_Schema::Tables::IncomeTablePtr;
    std::cout << terminalFormatingColorcodes::ANSI_RESET;
    while (sessionSwitch)
    {
        BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("BudgetCpp v0.2", terminalFormatingColorcodes::ANSI_BG_WHITE);
        BCPP_Package_TerminalUI::formattedOutputs::optionsMenu(true, menuOptions);
        menuSelection = BCPP_Package_TerminalUI::formattedPrompts::FormattedPrompts::customPrompt<char>(":>");
        switch (menuSelection)
        {
        case 'q':
            sessionSwitch = !sessionSwitch;
            break;

        case 't':
        {
            int tableSelection = 0;
            menusession = true;
            while (menusession)
            {
                BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("Table View", terminalFormatingColorcodes::ANSI_BG_GREEN);
                BCPP_Package_TerminalUI::formattedOutputs::optionsMenu(false, tableMenuOptions);
                BCPP_Package_TerminalUI::formattedOutputs::printHeaders(tableSelection, tableTabs, terminalFormatingColorcodes::ANSI_BG_MAGENTA, terminalFormatingColorcodes::ANSI_BG_BLACK);
                std::cout<<BCPP_Interface::output::Account::returnBalance(*currentPointer)<<"\n";
                BCPP_Interface::output::displayTable(*currentPointer);
                optionSelection = BCPP_Package_TerminalUI::formattedPrompts::FormattedPrompts::customPrompt<char>(":>");
                /*
                    q = quit
                    i = insert
                    d = delete
                */
                switch (optionSelection)
                {
                case 'q':
                    menusession = false;
                    break;

                case 'i':
                {
                    std::cout<<"Enter Name of Transaction ";
                    std::string expenseName = BCPP_Package_TerminalUI::formattedPrompts::FormattedPrompts::customPrompt<std::string>("&:");
                    auto returndata = BCPP_Package_TerminalUI::formattedPrompts::FormattedPrompts::customPromptFormDualInputs<float, float>(
                        "Row Input\n Enter Values for the Row",
                        "$:",
                        "Input Debit Amount",
                        "Input Credit Amount",
                        terminalFormatingColorcodes::ANSI_BG_RED,
                        terminalFormatingColorcodes::ANSI_BG_BLUE);
                    BCPP_Interface::dataManipulation::insertData(*currentPointer,expenseName, returndata.first, returndata.second);
                    break;
                }

                case 'r':
                {
                    int returnData = BCPP_Package_TerminalUI::formattedPrompts::FormattedPrompts::customPrompt<int>("Enter Row:");
                    BCPP_Package_TerminalUI::formattedOutputs::generateTitleBar("RowView", terminalFormatingColorcodes::ANSI_BG_RED);
                    BCPP_Interface::output::displayRowByIndex(*currentPointer, returnData - 2);
                    BCPP_Package_TerminalUI::formattedOutputs::addMarker(terminalFormatingColorcodes::ANSI_BG_RED);
                    BCPP_Interface::output::displayRowByIndex(*currentPointer, returnData - 1);
                    BCPP_Package_TerminalUI::formattedOutputs::resetMarker();
                    BCPP_Interface::output::displayRowByIndex(*currentPointer, returnData);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    break;
                }

                case 'S':
                {
                    *currentPointer = (*currentPointer == BCPP_Database_Schema::Tables::IncomeTablePtr) ? BCPP_Database_Schema::Tables::ExpenseTablePtr : BCPP_Database_Schema::Tables::IncomeTablePtr;
                    
                    break;
                }

                default:
                    break;
                }
            }
        }

        default:
            break;
        }
    }
}