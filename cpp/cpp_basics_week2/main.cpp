/*
    Week 2 assignment C++ foundations

    about std::endl vvv
    https://gcc.gnu.org/onlinedocs/libstdc++/manual/streambufs.html#io.streambuf.buffering

    Started writing this program with the believe that std::endl was the way to go. I thought this was explained in the lessons but
    I might have misheard. Anyway I switched to \n for the rest of assignment.

    Also 80% of this program was written with the believe that transaction was referring to money. Hence some variable names that have
    more to do with accounting than tracking of used memory.
*/

#include <fstream>
#include <stdio.h>

#include "utils.h"
#include "transaction.h"
#include "user_menu.h"

using transactions::TransactionGroup;

int main()
{
    std::ifstream stream = std::ifstream("./files/trans.txt");
    TransactionGroup group = TransactionGroup(stream);
    // menu::enterMenuLoop(group);

    group.printPoolCustom();

    cout << "Goodbye!";
    return 0;
}
