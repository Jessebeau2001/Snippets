#include <iostream>
#include <mutex>

#include "TaskManager.h"

using std::cout;

struct intLimit
{
    int value;
};

int main()
{
    FooTask foo_task = FooTask();
    BarTask bar_task = BarTask();

    DynamicArray<ITask*> task_array = DynamicArray<ITask*>(5);
    
    task_array.append((ITask*) &foo_task);
    task_array.append((ITask*) &bar_task);

    for (int i = 0; i < task_array.getCount(); i++)
    {
        task_array[i]->run();
    }

    cout << "Elements: " << task_array.getCount() << ", size: " << task_array.getSize() << ", size in memory: " << task_array.getSize() * sizeof(ITask*) << "\n";
    task_array.shrinkFit();
    cout << "Elements: " << task_array.getCount() << ", size: " << task_array.getSize() << ", size in memory: " << task_array.getSize() * sizeof(ITask*);

    return 0;
}

void bufferTest()
{
    ITask ** buf = new ITask*[2];

    FooTask f_task = FooTask();
    BarTask b_task = BarTask();

    buf[0] = (ITask*) &f_task;
    buf[1] = (ITask*) &b_task;

    buf[0]->run();
    buf[1]->run();
}

void dynamicArrayTest()
{   // Pulled from StackOverflow
    int *p;
    p = new int[5];
    for(int i=0;i<5;i++)
        *(p+i)=i;

    // realloc
    int* temp = new int[6];
    std::copy(p, p + 5, temp);
    delete [] p;
    p = temp;
}

void taskManagerTest()
{
    TaskManager manager = TaskManager(5);

    FooTask f_task = FooTask();
    BarTask b_task = BarTask();

    manager.addTask((ITask*) &f_task);
    manager.update();
    manager.addTask((ITask*) &b_task);
    manager.update();
}

void dynamicArrayObjTest()
{
    DynamicArray<int> arr = DynamicArray<int>(0);
    arr.append(5);
    arr.append(7);
    arr.append(9);

    for (int i = 0; i < arr.getCount(); i++)
    {
        cout << arr[i] << "\n";
    }

    cout << "Array size: " << arr.getSize();
}

void dynamicArrayPointerTest()
{

}