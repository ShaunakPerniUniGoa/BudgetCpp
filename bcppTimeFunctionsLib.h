#include <ctime>

namespace BudgetCppTimeObjects
{
    enum timePreoid
    {
        DAILY,
        WEEKLY,
        MONTHLY,
        ANNUALLY
    };
}

namespace BudgetCppTimeFunctions
{
    std::tm getCurrentDate()
    {
        std::time_t currentTime = std::time(nullptr);
        std::tm *currentDateTime = std::localtime(&currentTime);
        return *currentDateTime;
    }

    int daysDifference(std::tm dateStart, std::tm dateEnd)
    {
        std::time_t timeStart = std::mktime(&dateStart);
        std::time_t timeEnd = std::mktime(&dateEnd);
        std::time_t diff = std::difftime(timeEnd, timeStart);
        int Days = diff / (60 * 60 * 24);
        return Days;
    }

    int weekDifference(std::tm dateStart, std::tm dateEnd)
    {
        int days = daysDifference(dateStart, dateEnd);
        int weeks = days / 7;
        return weeks;
    }

    int yearDifference(std::tm dateStart, std::tm dateEnd)
    {
        int years = dateEnd.tm_year -  dateStart.tm_year;
        return years;
    }

    int MonthDifference(std::tm dateStart, std::tm dateEnd)
    {
        int yeardiff = yearDifference(dateStart,dateEnd);
        int months = (dateEnd.tm_mon - dateStart.tm_mon)/12*yeardiff;
        return months;
    }
};