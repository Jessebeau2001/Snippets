#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::ostringstream;
using std::string;
using std::vector;

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
            oss << "ID: " << id << ", Value: " << value;
            return oss.str();
        }
    };

    struct TransactionGroup
    {
        vector<Transaction> t_list;

        TransactionGroup(ifstream & stream)
        {
            std::string line{};
            int cLine = 0;

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
                cLine++;
            }
        }

        void printContent()
        {
            for (auto & item : t_list)
            {
                cout << item.toString() << endl;
            }
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
    };
}

#endif