#include <vector>
struct AccountingRow{
    
};
template <typename RowType> class AccountingTable{
    private:
    std::vector<RowType> tableColumns;
    public:
    AccountingTable(RowType[] inputRows){
        for(RowType a : inputRows){
            tableColumns.insert(a);
        }
    }
};