/*
    Created By Shaunak Perni
    MIT License
*/

#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>

template <typename columnStruct>
class vectorDataTable
{
private:
    std::vector<columnStruct> table;

public:
    #pragma region CURD
    void insert(const columnStruct &row)
    {
        table.push_back(row);
    }

    const std::vector<columnStruct> &getAllRows() const
    {
        return table;
    }

    bool update(int index, const columnStruct &newRow)
    {
        if (index >= 0 && index < static_cast<int>(table.size()))
        {
            table[index] = newRow;
            return true;
        }
        return false;
    }

    bool drop(int index)
    {
        if (index >= 0 && index < static_cast<int>(table.size()))
        {
            table.erase(table.begin() + index);
            return true;
        }
        return false;
    }
    #pragma endregion
    #pragma region FUCTIONS
    std::size_t getSize() const
    {
        return table.size();
    }

    template<typename column>
    column Sum(column columnStruct::*columnptr) const
    {
        column sum = column();
        for (const auto& row : table)
        {
            sum += row.*columnptr;
        }
    }


};