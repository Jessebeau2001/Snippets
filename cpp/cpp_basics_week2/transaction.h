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
            oss << index + 1 << " \t| ID: " << id << "\t | Value: " << value;
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

        int numTransactions();
        int maxPoolSize();
        int returnedByTerminate(string id, int index);
        int sumPoolSize();
        int askSize();

        bool isValid();
        bool shrinkUntilFit(int size_max);

        void handleClaim(Transaction t, int & size);
        void printIncreaseFull();
        void printIncreaseSelect();
        void printSumCapped();
        void printPoolInfo();
        void printIdentifiers();
        void editPool();
        
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
