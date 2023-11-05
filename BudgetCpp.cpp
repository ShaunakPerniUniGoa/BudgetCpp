#include "bcppTableObjectsLib.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

namespace BudgetCppAppObjects
{
    struct accountingRow
    {
        int serialNumber;
        std::string itemName;
        float valueMoney;
        std::tm EntryDate;
    };
}

namespace BudgetCppAppBackEnd
{
    auto columnValueSelection = [](const BudgetCppAppObjects::accountingRow row){ return row.valueMoney; };

    budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow> IncomeTable;
    budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow> ExpenseTable;

    budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow>* IncomeTablePointer = &IncomeTable;
    budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow>* ExpenseTablePointer = &ExpenseTable;

    std::vector<budgetCppTableObjects::AutomatedAccountingObject<BudgetCppAppObjects::accountingRow>> automatedIncomeObjects;
    std::vector<budgetCppTableObjects::AutomatedAccountingObject<BudgetCppAppObjects::accountingRow>> automatedExpensebjects;

    

    float returnTotalValue(budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow> *tableRef)
    {
        float total = tableRef->sumMembers<float>(columnValueSelection);
        return total;
    }

    void triggerAutomatedObjects(std::vector<budgetCppTableObjects::AutomatedAccountingObject<BudgetCppAppObjects::accountingRow>> *automatedObjectsVector)
    {
        for (budgetCppTableObjects::AutomatedAccountingObject<BudgetCppAppObjects::accountingRow> &object : *automatedObjectsVector)
        {
            object.checkConditionAndTrigger();
        }
    }

    int getLastSr(budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow>* pointer)
    {
        return (pointer->getRowCount() > 0) ? pointer->getTail().serialNumber : 0;
    }

    void insertRowIntoTable(budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow>* tablepointer,std::string itemName="NULL", float valueMoney=0.0)
    {
        int Srlast = getLastSr(tablepointer) + 1;
        std::tm currentDate = BudgetCppTimeFunctions::getCurrentDate();
        tablepointer->insertRow({Srlast,itemName,valueMoney,currentDate});
    }

}

namespace BudgetCppAppFrontEnd
{
    std::string const COLUMN_HEADERS = "Sr\tItem\tValue\tDate\n";
    void printTableContents(budgetCppTableObjects::AccountingTableObject<BudgetCppAppObjects::accountingRow> *tableref)
    {
        std::cout << COLUMN_HEADERS;
        for (const auto &currentRow : tableref->getAllRows())
        {
            std::cout<<currentRow.serialNumber<<"\t"<<currentRow.itemName<<"\t"<<currentRow.valueMoney<<"\t"<<BudgetCppTimeDataStringFormatting::returnFormatedDate(currentRow.EntryDate)<<std::endl;
        }
    }
}

int main()
{
    using namespace BudgetCppAppFrontEnd;
    using namespace BudgetCppAppBackEnd;

    while(true){
        
    }
    
    return 0;
}
