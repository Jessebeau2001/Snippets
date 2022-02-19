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

    void TransactionGroup::printPoolCustom()
    {
        auto size = askSize();
        PoolStat stat{*this, size};

        if (stat.ok) {
            stat.print(PoolStat::FULL);
        } else {
            stat.print(PoolStat::LIMITED);
        }
    }

    bool TransactionGroup::shrinkUntilFit(PoolStat * stat_container)    // Set this back to int for things to work again
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

/*
    Cannot remove first transaction
    Cannot remove negative transaction
    ------>
    mark second positive appearance
    put in list and sort
    remove biggest
    if still larger than max, do again
*/