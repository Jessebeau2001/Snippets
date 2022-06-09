#include <iostream>
#include <mutex>

#include "TaskManager.h"

using std::cout;

int main()
{
    TaskManager manager = TaskManager(5);

    FooTask f_task = FooTask();
    BarTask b_task = BarTask();

    manager.addTask((ITask*) &f_task);
    manager.update();
    manager.addTask((ITask*) &b_task);
    manager.update();
    
    // ITask ** buf = new ITask*[2];

    // buf[0] = (ITask*) &f_task;
    // buf[1] = (ITask*) &b_task;

    // buf[0]->run();
    // buf[1]->run();

    return 0;
}