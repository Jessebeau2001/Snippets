#ifndef USER_MENU_H
#define USER_MENU_H

#include "transaction.h"

using transactions::TransactionGroup;

namespace menu
{
    static const string txt = "";
    enum Options { COUNT = 1, MIN_SIZE, VIEW_ALL, FIND_ID, SUM_CLAIMS, LIST_IDENTIFIERS, VALIDATE, MAX, POOL_SIZE, QUIT };
    
    void printAllOptions();
    bool runMenuAction(TransactionGroup & group, Options option);
    void enterMenuLoop(TransactionGroup & group);
}

#endif