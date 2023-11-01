#include "bcppTableObjects.h"
#include <vector>

budgetCppTableObjects::AccountingTableObject<budgetCppTableObjects::accountingRow> IncomeTable;
budgetCppTableObjects::AccountingTableObject<budgetCppTableObjects::accountingRow> ExpenseTable;

std::vector<budgetCppTableObjects::AutomatedAccountingObject<budgetCppTableObjects::accountingRow>> automatedIncomeObjects;
std::vector<budgetCppTableObjects::AutomatedAccountingObject<budgetCppTableObjects::accountingRow>> automatedExpensebjects;

int main(){

    return 0;
}