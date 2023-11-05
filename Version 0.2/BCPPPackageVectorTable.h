#include <vector>
#include <string>

namespace BCPP_Package_VectorTable
{
    template <typename columnsTypeStruct>
    class VectorTableInterface
    {
        public:
            virtual void pushRow(columnsTypeStruct row)= 0;
            virtual columnsTypeStruct &returnRow(int indexKey)= 0;
            virtual columnsTypeStruct &getTail() = 0;
            virtual columnsTypeStruct &getHead() = 0;
            virtual void updateRow(int indexKey, columnsTypeStruct row) = 0;
            virtual void deleteRow(int indexKey)= 0;
    };

    template <typename columnsTypeStruct>
    class VectorTable : public VectorTableInterface<columnsTypeStruct>
    {
    private:
        std::vector<columnsTypeStruct> vectorTable;

    public:
        VectorTable(){};
        void pushRow(columnsTypeStruct row)
        {
            vectorTable.push_back(row);
        }

        columnsTypeStruct &returnRow(int indexKey)
        {
            return vectorTable[indexKey];
        }

        columnsTypeStruct &getTail()
        {
            return vectorTable.back();
        }

        columnsTypeStruct &getHead()
        {
            return vectorTable.begin();
        }

        void updateRow(int indexKey, columnsTypeStruct row)
        {
            indexKey > vectorTable.size() ? indexKey = vectorTable.size() - 1 : indexKey = indexKey;
            vectorTable.at(indexKey) = row;
        }

        void deleteRow(int indexKey)
        {
            indexKey > vectorTable.size() ? indexKey = vectorTable.size() - 1 : indexKey = indexKey;
            vectorTable.erase(vectorTable.begin + indexKey);
        }

        const std::vector<columnsTypeStruct> &returnAllRows()
        {
            return vectorTable;
        }

        template <typename MemberType, typename MemberSelector>
        MemberType sumMember(MemberSelector selector) const
        {
            MemberType total = MemberType{};
            for (const columnsTypeStruct &row : vectorTable)
            {
                total += selector(row);
            }
            return total;
        }
    };
}