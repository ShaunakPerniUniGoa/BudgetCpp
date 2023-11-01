#include <ctime>

namespace BudgetCppTimeFunctions{
    std::tm getCurrentDate(){
        std::time_t currentTime = std::time(nullptr);
        std::tm* currentDateTime = std::localtime(&currentTime);
        return *currentDateTime;
    } 
};