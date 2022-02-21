#include "transaction.h"

#include <algorithm>

namespace transactions
{
    /// Lambda for value sorting
    bool compare_value(Transaction * a, Transaction * b) {
        return a->value > b->value;
    }

    /// Lambda for index sorting
    bool compare_index(Transaction * a, Transaction * b) {
        return a->index > b->index;
    }

    /**
     * Gets number of Transactions in the group by returning size of vector holder transactions, being t_list.
     * @return Number of transactions in group.
     */
    int TransactionGroup::numTransactions()
    {
        return t_list.size();
    }

    /**
     * Calculates the maximum size the group will ever reach.
     * @return Maximum pool size.
     */
    int TransactionGroup::maxPoolSize()
    {
        int size{};
        int maxSize{};
        for (auto & t : t_list) {
            handleClaim(t, size);
            if (size > maxSize) maxSize = size;
        }
        return maxSize;
    }

    /**
     * Calculates amount of data taken up by Transaction of specified id and returns this amount.
     * WARNING: claim terminate indexes still have to be implemented meaning that this function currently
     * only behaves correctly specified id only terminates once throughout process.
     * @param id Transaction id to terminate.
     * @param index WARNING: value not implemented
     * @return Amount of bytes restored by terminating claim.
     */
    int TransactionGroup::returnedByTerminate(string id, int index)
    {
        int inUse{};
        for (auto & t : t_list) {
            if (t.id == id) inUse += t.value;
        }
        return inUse;
}

    /**
     * Calculates full size of the pool after all transactions impacts have been applied.
     * @return Final size of the pool.
     */
    int TransactionGroup::sumPoolSize()
    {
        int size{};
        for (auto & t : t_list) {
            handleClaim(t, size);
        }
        return size;
    }

    /**
     * Checks whether none of the claim will ever fall below 0, thus verifying the validity of the group.
     * @return True when no claim ever falls below 0.
     */
    bool TransactionGroup::isValid()
    {
        for (auto & key : keys) {
            int sum{};
            for (auto & item : t_list) {
                if (item.id == key) handleClaim(item, sum);
            }
            if (sum < 0) return false;
        }
        return true;
    }

    /**
     * Calculates claim impact on the group and applies it to size paramater.
     * @param t Transaction to take care of.
     * @param size Group's size to apply transaction impact on.
     */
    void TransactionGroup::handleClaim(Transaction t, int & size)
    {
        if(t.active == false) return;
        if (t.value == 0) {
            size -= returnedByTerminate(t.id, 1);
        }
        size += t.value;
    }

    /**
     * Prints the sum of all transaction values, and calculations leading to these values, in the group.
     * See printIncreaseSelect() to print specific Transactions.
     */
    void TransactionGroup::printIncreaseFull()
    {
        int sum{};
        for (auto & item : t_list) {
            handleClaim(item, sum);
            cout << item.toString() << " \ttotal: " << sum << "\n";
        }
    }

    /**
     * Prints the sum of specified transaction values, and calculations leading to these values, in the group.
     * See printIncreaseFull() to print all Transactions.
     */
    void TransactionGroup::printIncreaseSelect()
    {
        int sum{};
        string id{};
        bool found = false;

        cout << "Enter ID: ";
        cin >> id;
        
        for (auto & item : t_list) {
            if (item.id == id) {
                handleClaim(item, sum);
                cout << item.toString() << " \ttotal: " << sum << "\n";
                found = true;
            }
        }

        if (!found) cout << "id '" << id << "' was not found" << "\n";
    }

    /**
     * Prints the sum of values based on user inputted index. If the user omitted
     * value is greater than the number of transactions in the group it will auto default
     * to this maximum number.
     */
    void TransactionGroup::printSumCapped()
    {
        cout << "Until when: ";
        int cap = parseInt();
        if (cap > numTransactions()) {
            cout << cap << " is greater than amount of transactions in this group (" << numTransactions() << "), defaulting to max.\n";
            cap = numTransactions();
        }
        int size{};
        for (int i = 0; i < cap; i++) {
            handleClaim(t_list[i], size);
        }
        cout << "Sum of specified claims is " << size << " bytes.\n";
    }

    /**
     * Asks the user to input an integer size using utils::parseInt(). This function will keep on looping until a valid
     * integer is inputted in the console.
     * @returns Appended int from console.
     */
    int TransactionGroup::askSize()
    {
        cout << "Enter pool size: ";
        return parseInt();
    }

    /**
     * Prints unique keys (or identifiers) about the group. These keys are stored in a set when the object is initialized.
     */
    void TransactionGroup::printIdentifiers()
    {
        cout << "Unique identifiers for this group are:\n";
        for (auto & key : keys) {
            cout << " - " << key << "\n";
        }
    }

    /**
     * Prints some important statistics about the group and it's memory usage.
     */
    void TransactionGroup::printPoolInfo()
    {
        auto size = askSize();
        PoolStat stat{*this, size};
        stat.print(PoolStat::FULL);
    }

    /**
     * Prompts user to input a hypothetical pool size, then tries to fit the current group within given size.
     * Group fits: Prints stats.
     * Group can fit: Applies changes so group can fit within size, then prints stats.
     * Group can't fit: Alerts user that group can never fit.
     */
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
     * @return Vector with pointers to Transactions valid for deletion.
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