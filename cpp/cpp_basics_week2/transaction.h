#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "utils.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ostringstream;
using std::string;
using std::vector;
using std::set;
using utils::parseInt;

namespace transactions
{
    struct Transaction
    {
        string id;
        int value;
        int index;
        bool active = true;

        Transaction(string id, int value, int index)
        {
            this->id = id;
            this->value = value;
            this->index = index;
        }

        string toString()
        {
            ostringstream oss;
            oss << index << " \t| ID: " << id << "\t | Value: " << value;
            return oss.str();
        }
    };

    struct TransactionGroup
    {
        vector<Transaction> t_list; // Full list
        set<string> keys;           // Keys / Unique identifiers

        TransactionGroup(ifstream & stream)
        {
            std::string line{};     // List of all transactions
            int index = 0;          // List of sums

            while (std::getline(stream, line))
            {
                std::size_t itt = line.find(' ');
                string id = (line.substr(0, itt));
                int value{};
                
                try { 
                    value = stoi(line.substr(itt));
                } catch (std::exception e) {
                    cout << "Could not read value for line " << index + 1 << " (with id: " << id << "), please check source file" << endl;
                    value = 0;
                }

                t_list.insert(t_list.end(), Transaction(id, value, index));
                keys.insert(id);
                index++;
            }
            t_list.shrink_to_fit();
        }

        int numTransactions()
        {
            return t_list.size();
        }

        int maxPoolSize()
        {
            int size{};
            int maxSize{};

            for (auto & t : t_list) {
                handleClaim(t, size);
                if (size > maxSize) maxSize = size;
            }

            return maxSize;
        }

        // add index checks (maybe with iterators)
        int returnedByTerminate(string id, int index)
        {
            int inUse{};
            for (auto & t : t_list) {
                if (t.id == id) inUse += t.value;
            }
            return inUse;
        }

        int sumPoolSize()
        {
            int size{};
            for (auto & t : t_list) {
                handleClaim(t, size);
            }
            return size;
        }
        
        bool isValid()
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

        void handleClaim(Transaction t, int & size)
        {
            if(t.active == false) return;
            if (t.value == 0) {
                size -= returnedByTerminate(t.id, 1);
            }
            size += t.value;
        }

        void printIncreaseFull()
        {
            int sum{};
            for (auto & item : t_list) {
                handleClaim(item, sum);
                cout << item.toString() << " \ttotal: " << sum << "\n";
            }
        }

        void printIncreaseSelect()
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

        void printSumCapped()
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

        int askSize()
        {
            cout << "Enter pool size: ";
            return parseInt();
        }
        
        void printIdentifiers()
        {
            cout << "Unique identifiers for this group are:\n";
            for (auto & key : keys) {
                cout << " - " << key << "\n";
            }
        }

        void printPoolInfo();
        void printPoolCustom();

        bool shrinkUntilFit(PoolStat * stat_container);
        vector<Transaction *> getGarbadge();
    };

    struct PoolStat
    {
        enum Range { LIMITED, FULL };

        int size_max, size_final;
        int remainder_max, remainder_final;
        bool ok{};

        PoolStat(TransactionGroup & group, int cap)
        {
            size_max = group.maxPoolSize();
            size_final = group.sumPoolSize();
            remainder_max = cap - size_max;
            remainder_final = cap - size_final;
            ok = (remainder_max > 0);
        }

        void print(Range r = LIMITED)
        {
            cout << "\nStatus: " << (ok ? "OK" : "NOT OK") << "\n";
            if (r == FULL) {
                cout << "Free pool at end: " << remainder_final << "\n";
                cout << "Free pool under max load: " << remainder_max << "\n";
            }
        }
    };
}

#endif
