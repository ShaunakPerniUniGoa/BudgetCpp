#include "BCPPPackageVectorTable.h"
#include "../bcppTimeFunctionsLib.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>

namespace terminalFunctions
{
#define CLEARSCREENCOMMAND "clear"
    void clearScreen()
    {
        std::system(CLEARSCREENCOMMAND);
    }
}

namespace tableObjects
{
    struct auditorumDBrow
    {
        int id;
        char blockname;
        int blockSize;
    };

    std::string ROWHEADERS = "Block\tCapacity\n";

    std::string ROWHEADERSBOOK = "Block\tBooked Date\n";

    struct bookingsDBRow
    {
        int id;
        int fkeyAuditorium;
        std::tm assignedDate;
    };
}

BCPP_Package_VectorTable::VectorTable<tableObjects::auditorumDBrow> auditoriumDB; // Database::
BCPP_Package_VectorTable::VectorTable<tableObjects::bookingsDBRow> bookingsDB;    // Database ::

void displayMenu(std::vector<std::string> menuOptions)
{
    for (std::string option : menuOptions)
    {
        std::cout << option << "\n";
    }
}

template <typename returnType>
returnType customPrompt(std::string promptSymbol)
{
    returnType inputCapture;
    std::cout << promptSymbol;
    std::cin >> inputCapture;
    return inputCapture;
}

template <typename returnType>
returnType customPrompt(std::string promptSymbol, std::string promptMessage)
{
    returnType inputCapture;
    std::cout << promptMessage << promptSymbol;
    std::cin >> inputCapture;
    return inputCapture;
}

template <typename translationType>
translationType boolTranslate(bool inputbool, translationType ifTrueVal, translationType ifFalseVal)
{
    if (inputbool)
    {
        return ifTrueVal;
    }
    else
    {
        return ifFalseVal;
    }
}

void printAudDB()
{
    std::cout << tableObjects::ROWHEADERS;
    for (auto row : auditoriumDB.returnAllRows())
    {
        std::cout << row.blockname << "\t" << row.blockSize << "\n";
    }
}

char returnAudChar(int id)
{
    return auditoriumDB.returnRow(id).blockname;
}

void createNewAuditorium()
{
    int last = auditoriumDB.returnSize();
    char newBlockName = customPrompt<char>("&:", "Enter Block Name: ");
    int blockSize = customPrompt<int>("$:", "Enter Block Size ");
    auditoriumDB.pushRow({last, newBlockName, blockSize});
}

int returnAudIDOnName(char AudName)
{
    for (auto &row : auditoriumDB.returnAllRows())
    {
        if (AudName == row.blockname)
        {
            return row.id;
        }
    }
    return -1;
}

bool checkBookingOnDate(char AuditorimName, std::tm date) //!!!CHECK THIS FUNCTION 
{
    int Aid = -1;

    for (auto &row : auditoriumDB.returnAllRows()) {
        if (AuditorimName == row.blockname) {
            Aid = row.id;
            break;
        }
    }

    for (auto &rowB : bookingsDB.returnAllRows()) {
        if (Aid == rowB.fkeyAuditorium) {
            if (date.tm_mday == rowB.assignedDate.tm_mday &&
                date.tm_mon == rowB.assignedDate.tm_mon &&
                date.tm_year == rowB.assignedDate.tm_year) {
                return false;
            }
        }
    }

    return true;
}

void addNewBooking()
{
    int last = bookingsDB.returnSize();
    char AudName = customPrompt<char>("Enter the Auditorium that you wish to book:");
    int fkeyID = returnAudIDOnName(AudName);
    if (fkeyID > -1)
    {
        
    }
    else
    {
        std::cout << "Invalid Auditorium";
    }
    std::tm parsedDate = {};
    parsedDate.tm_mday = customPrompt<int>("DD%:");
    parsedDate.tm_mon = customPrompt<int>("MM%:");
    parsedDate.tm_year = customPrompt<int>("YY%:") - 1900;
    bool valid = checkBookingOnDate(AudName, parsedDate);
    if (valid)
    {
        bookingsDB.pushRow({
            last,fkeyID,parsedDate
        });
    }
    else
    {
        std::cout << "WARN! Booking Unsuccessful! Auditorium is already Booked on that Date!";
        customPrompt<char>("Press Any Key");
    }
}

void retunBookingTable()
{
    std::cout<<tableObjects::ROWHEADERSBOOK;
    for(auto row : bookingsDB.returnAllRows())
    {
        std::cout<< returnAudChar(row.fkeyAuditorium) << "\t" << BudgetCppTimeDataStringFormatting::returnFormatedDate(row.assignedDate)<<"\n";
    }
}
int main()
{
    char menuOption;
    bool sessionSwitch = true;
    bool editorSessionSwitch = false; // set to true when a option is selected
    char submenuOption;
    while (sessionSwitch)
    {
        terminalFunctions::clearScreen();
        displayMenu({"\n(e)dit Auditorim Details", "(b)ook", "(q)uit"});
        menuOption = customPrompt<char>("Enter any of the given options $:   ");
        switch (menuOption)
        {
        case 'q':
            sessionSwitch = false;
            break;

        case 'e':
            editorSessionSwitch = true;
            while (editorSessionSwitch)
            {
                terminalFunctions::clearScreen();
                displayMenu({"(i)nsert new Auditorium ", "(q)uit "});
                std::cout << "\n";
                printAudDB();
                submenuOption = customPrompt<char>("Enter an $: ");
                switch (submenuOption)
                {
                case 'q':
                    editorSessionSwitch = false;
                    break;
                case 'i':
                    createNewAuditorium();
                }
            }
            break;

        case 'b':
            editorSessionSwitch = true;
            while (editorSessionSwitch)
            {
                terminalFunctions::clearScreen();
                displayMenu({
                             "(b)ook an Auditorium",
                             "(q)uit "});
                std::cout << "\n";
                retunBookingTable();
                submenuOption = customPrompt<char>("Enter an $: ");
                switch (submenuOption)
                {
                case 'q':
                    editorSessionSwitch = false;
                    break;
                case 'b':
                    terminalFunctions::clearScreen();
                    printAudDB();
                    addNewBooking();
                }
            }
            break;

        default:
            break;
        }
    }
}