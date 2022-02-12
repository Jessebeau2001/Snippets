#include "BruhSort.h"

void bsrt::swap(int &a, int &b)
{
    auto temp = a;
    a = b;
    b = temp;
}

bool bsrt::sortOnce(int * arr, int size)
{
    bool done = true;
    
    for (int i = 1; i < size; i++) {
        if(arr[i] < arr[i - 1]) {
            swap(arr[i], arr[i - 1]);
            done = false;
        }
    }
    
    return done;
}

void bsrt::sort(int * arr, int size)
{
    if (size < 2) return;                       // Return when only 1 element in array.
    while (sortOnce(arr, size) == false);
}