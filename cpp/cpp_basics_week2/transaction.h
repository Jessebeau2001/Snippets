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

namespace transactions
{
    struct Transaction
    {
        string id;
        int value;

        Transaction(string id, int value)
        {
            this->id = id;
            this->value = value;
        }

        string toString()
        {
            ostringstream oss;
            oss << "ID: " << id << " \tValue: " << value;
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
            int cLine = 0;          // List of sums

            while (std::getline(stream, line))
            {
                std::size_t itt = line.find(' ');
                string id = (line.substr(0, itt));
                int value{};
                
                try { 
                    value = stoi(line.substr(itt));
                } catch (std::exception e) {
                    cout << "Could not read value for line " << cLine + 1 << " (with id: " << id << "), please check source file" << endl;
                    value = 0;
                }

                t_list.insert(t_list.end(), Transaction(id, value));
                keys.insert(id);
                cLine++;
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

            for (auto t : t_list) {
                if (t.value == 0) size -= HandleClaimTerm(t.id);
                size += t.value;
                if (size > maxSize) maxSize = size;
            }

            return maxSize;
        }
        
        int HandleClaimTerm(string id)
        {
            int size{};
            for (auto t : t_list) if (t.id == id) size += t.value;
            return size;
        }

        bool isValid()
        {
            for (auto & key : keys) {
                int sum{};
                for (auto & item : t_list) {
                    if (item.id == key) handleIncrease(sum, item);
                }
                if (sum < 0) return false;
            }
            return true;
        }

        void printIncreaseFull()
        {
            int sum{};
            for (auto & item : t_list) {
                handleIncrease(sum, item);
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
                    handleIncrease(sum, item);
                    cout << item.toString() << " \ttotal: " << sum << "\n";
                    found = true;
                }
            }

            if (!found) cout << "id '" << id << "' was not found" << "\n";
        }

        void handleIncrease(int & sum, Transaction item)
        {
            sum += item.value;
            if (item.value == 0) sum -= HandleClaimTerm(item.id);
        }

        void printSumCapped()
        {
            cout << "Until when: ";
            int cap = utils::parseInt();

            if (cap > numTransactions()) {
                cout << cap << " is greater than amount of transactions in this(" << numTransactions() << "), defaulting to max.\n";
                cap = numTransactions();
            }
            
            int size{};

            for (int i = 0; i < cap; i++) {
                if (t_list[i].value == 0) size -= HandleClaimTerm(t_list[i].id);
                size += t_list[i].value;
            }

            cout << "Sum of specified claims is " << size << " bytes.\n";
        }

        void printIdentifiers()
        {
            cout << "Unique identifiers for this group are:\n";
            for (auto & key : keys) {
                cout << " - " << key << "\n";
            }
        }
    };
}

#endif