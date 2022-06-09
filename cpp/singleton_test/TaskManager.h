#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "ISingleton.h"

class ITask
{
protected:
    short delay_ms = 0;
    bool halt = false;
    bool recurring = false;

public:
    virtual void run() = 0;
};

class FooTask : ITask
{
public:
    void run() override
    {
        std::cout << "I'm a Foo task!\n";
    }
};

class BarTask : ITask
{
public:
    void run() override
    {
        std::cout << "Bar task is me!\n";
    }
};

class TaskManager
{
private:
    int count = 0;
    int size;

    ITask ** task_list;

public:
    TaskManager(int default_size = 0) : size(default_size)
    {
        task_list = new ITask*[default_size];
    }

    void update()
    {
        if (count <= 0) return;

        auto i = count - 1;
        task_list[i]->run();
        task_list[i] = nullptr;
        count--;

    }

    bool addTask(ITask * task)
    {
        if (count > size)
            return false;
        
        task_list[count] = task;
        count++;
        return true;
    }

    ~TaskManager()
    {
        delete[] task_list;
    }


};

#endif