#ifndef BRUHSORT_H
#define BRUHSORT_H

#include <iostream>

class bsrt
{
    public:
        static void swap(int &a, int &b);              // Swap 2 ints.
        static void sort(int * arr, int size);         // Sorts an array of ints.

    private:
        static bool sortOnce(int * arr, int size);     // Applies sort once over array of ints. Returns true if no changes.
};

#endif