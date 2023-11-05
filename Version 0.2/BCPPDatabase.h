#include "BCPPPackageVectorTable.h"
#include "BCPPPackageTimeLib.h"
namespace BCPP_Database_Objects
{
    namespace RowStructures
    {
        struct structAccountingRow
        {
            int serialNumber;
            std::string itemName;
        };
    }
}

namespace BCPP_Database_Schema
{
    namespace Tables
    {
        BCPP_Package_VectorTable::VectorTable<BCPP_Database_Objects::RowStructures::structAccountingRow> IncomeTable;
        BCPP_Package_VectorTable::VectorTable<BCPP_Database_Objects::RowStructures::structAccountingRow> *IncomeTablePtr = &IncomeTable;
        
        BCPP_Package_VectorTable::VectorTable<BCPP_Database_Objects::RowStructures::structAccountingRow> ExpenseTable;
        BCPP_Package_VectorTable::VectorTable<BCPP_Database_Objects::RowStructures::structAccountingRow> *ExpenseTablePtr = &ExpenseTable;
    }

    namespace TriggersObjectsContainers
    {

    }
}

namespace BCPP_Interface
{
    namespace formattedPrompts
    {

    }
}