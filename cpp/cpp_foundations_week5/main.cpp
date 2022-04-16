/*
    Week 3 assignment C++ foundations
    By Jesse Visscher, 477437, ETI1v.B'
*/

#include <iostream>
#include "tracker.h"
#include "simple.h"

void print_usage()
{
    std::cout << "Instances | " << Simple::tracker().instances() << "\n";
    std::cout << "Memory    | " << Simple::tracker().memory() << "\n";
}

void count()
{
    Simple s_func1{0};
    Simple s_func2{1};

    print_usage();
    {
        Simple s_internal{3};
        print_usage();
    }
    print_usage();
}

int main()
{
    Simple s_main{42};
    print_usage();
    count();
    print_usage();
    return 0;
}