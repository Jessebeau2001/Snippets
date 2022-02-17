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
                cout << "There are " << group.numTransactions() << " transactions in this group.";
                break;
            case MIN_SIZE:
                cout << "System needs a minimum size of " << group.maxPoolSize() << " bytes.";
                break;
            case VIEW_ALL:
                cout << "Available transactions:\n";
                group.printContent();
                break;
            case FIND_ID:
                
                break;
            case QUIT:
                return true;
        }

        cout << "\n";
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