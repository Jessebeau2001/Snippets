#include "user_menu.h"

#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

namespace menu
{
    const string test = "";

    void printAllOptions()      // It's not ideal that there is a new stream being created every time the list is printed...
    {
        ifstream f{"./files/options.txt"};
        if (f.is_open()) cout << f.rdbuf() << endl;
    }

    bool runMenuAction(TransactionGroup & group, Options option)
    {
        switch(option)
        {
            default:
                break;
            case COUNT:
                cout << "There are " << group.numTransactions() << " transactions in this group.\n";
                break;
            case MIN_SIZE:
                cout << "System needs a minimum size of " << group.maxPoolSize() << " bytes.\n";
                break;
            case VIEW_ALL:
                cout << "Available transactions:\n";
                group.printIncreaseFull();
                break;
            case FIND_ID:
                group.printIncreaseSelect();
                break;
            case SUM_CLAIMS:
                group.printSumCapped();
                break;
            case LIST_IDENTIFIERS:
                group.printIdentifiers();
                break;
            case VALIDATE:
                std::cout << "List is " << (group.isValid() ? "valid" : "invalid") << ".\n";
                break;
            case MAX:
                break;
            case POOL_SIZE:
                break;
            case QUIT:
                return true;
        }
        return false;
    }

    void enterMenuLoop(TransactionGroup & group)
    {
        printAllOptions();
        bool exit = false;
        while (exit == false) {
            cout << "\n> ";
            exit = runMenuAction(group, (Options) utils::parseInt());
        }
    }
}