#include "bcppDataBaseSystem.h"
#include "terminalFormating.h"
#include <iostream>
#include <cstdlib>

void printHeaders(int selection, const std::vector<std::string> &Headers)
{
    for (long unsigned int nHeader = 0; nHeader < Headers.size(); nHeader++)
    {
        selection == nHeader ? std::cout << terminalFormatingColorcodes::ANSI_BG_GREEN << Headers[nHeader] << terminalFormatingColorcodes::ANSI_RESET << "\t" : std::cout << terminalFormatingColorcodes::ANSI_BG_WHITE << Headers[nHeader] << terminalFormatingColorcodes::ANSI_RESET << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    using namespace BudgetCppAppFrontEnd;
    using namespace BudgetCppAppBackEnd;
    using namespace terminalFormatingColorcodes;

    char c;
    bool sessionSwitch = true;
    int selectioncurrent = 0;
    int tables = BudgetCppAppBackEnd::tablePointersArray.size();
    std::vector<std::string> Headers = {"Income", "Expenses"};
    budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow> *currentTablePointer;

    while (sessionSwitch)
    {
        currentTablePointer = BudgetCppAppBackEnd::tablePointersArray[selectioncurrent];
        clearScreen();
        std::cout << ANSI_BG_WHITE << "BudgetCpp (v0.1)" << ANSI_RESET << std::endl
                  << std::endl;
        printHeaders(selectioncurrent, Headers);
        BudgetCppAppFrontEnd::printTableContents(currentTablePointer);
        std::cout << "$:";
        std::cin.get(c);
        switch (c)
        {

        case 's':
            std::cout << "Switch To Tab\n%:";
            std::cin >> selectioncurrent;
            selectioncurrent > tables ? selectioncurrent = tables - 1 : selectioncurrent = selectioncurrent;
            break;

        case 'i':
            std::cout << "Enter Value to table\n:>";
            BudgetCppAppFrontEnd::insertToTablePrompt(currentTablePointer);
            break;

        case 'q':
            sessionSwitch = !sessionSwitch;
            break;

        default:
            break;
        }
    }

    return 0;
}
