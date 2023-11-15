#include <ctime>
#include <sstream>
#include <iomanip>

namespace BCPP_Package_TimeLib
{
    namespace TimeObjects
    {
        enum TimePreoids
        {
            DAILY,
            WEEKLY,
            MONTHLY,
            YEARLY
        };
    }

    namespace TimeCalculationFunctions
    {
        std::tm getCurrentDate()
        {
            std::time_t currentTime = std::time(nullptr);
            std::tm *currentDateTime = std::localtime(&currentTime);
            return *currentDateTime;
        }
    }

    namespace timeDataFormatter
    {
        std::string returnFormatedDate(std::tm timeDate)
        {
            std::ostringstream formattedDate;
            formattedDate << std::setfill('0') << std::setw(2) << timeDate.tm_mday << '/'
                          << std::setfill('0') << std::setw(2) << timeDate.tm_mon + 1 << '/'
                          << timeDate.tm_year + 1900;
            return formattedDate.str();
        }
    }
}
