#include "transaction.h"

#include <algorithm>

namespace transactions
{
    bool compare_value(Transaction * a, Transaction * b) {
        return a->value > b->value;
    }

    bool compare_index(Transaction * a, Transaction * b) {
        return a->index > b->index;
    }

    void TransactionGroup::printPoolInfo()
    {
        auto size = askSize();
        PoolStat stat{*this, size};
        stat.print(PoolStat::FULL);
    }

    void TransactionGroup::editPool()
    {
        auto size = askSize();
        PoolStat stat{*this, size};

        if (stat.ok) {
            stat.print(PoolStat::FULL);
        } else {
            stat.print();
            bool fits = shrinkUntilFit(size);
            if (fits) {
                stat = PoolStat{*this, size};   // Update the stats in order to print correct info, it might be smart to print thew new stats within the shrink function so we dont have to update PoolState twice (here & in shrink).
                stat.print(PoolStat::FULL);     // But for now I want to keep it in there because this function should handle printing of all information, not the shrink function.
            } else {
                cout << "Group will never fit within specified range";
            }
        }
    }

    /**
     * Shrinks the group until its fits within the specified size.
     * @param size_max Desired size for group to fit in
     * @returns Bool whether it's possible to fit withing given size
     */
    bool TransactionGroup::shrinkUntilFit(int size_max)
    {
        PoolStat stat{*this, size_max};
        if(stat.ok) return true;
        auto marked = getGarbadge();

        for (auto m : marked) {
            cout << "Deleting: | " << m->toString() << "\n";
            m->active = false;
            stat = PoolStat{*this, size_max};
            if (stat.ok) return stat.ok;
        }

        return stat.ok;
    } 

    /**
     * Finds and sorts Transactions considered valid for deletion
     * based on their value.
     * @return Vector with pointers to deletable Transactions.
     */
    vector<Transaction *> TransactionGroup::getGarbadge()
    {
        vector<Transaction *> marked;
        set<string> seen;
        int size = numTransactions();

        for (int i = 0; i < size; i++) {
            bool present = seen.find(t_list[i].id) != seen.end();
            if(present && t_list[i].value > 0) {
                marked.push_back(&t_list[i]);
            } else {
                seen.insert(t_list[i].id);
            }
        }
        marked.shrink_to_fit();
        std::sort(marked.begin(), marked.end(), compare_value);
        return marked; 
    }
}