/*
    Jesse's inefficient as fuck sorting algorthim for cpp :)
*/

#include <iostream>

using std::cout;

void swap(int &a, int &b)
{
    auto temp = a;
    a = b;
    b = temp;
}

bool sortOnce(int * arr, int size)
{
    cout << "Do it again\n";
    bool done = true;
    
    for (int i = 1; i < size; i++) {
        if(arr[i] < arr[i - 1]) {
            swap(arr[i], arr[i - 1]);
            done = false;
        }
    }
    
    return done;
}

void sort(int * arr, int size)
{
    if (size < 2) return;
    
    while (!sortOnce(arr, size));
}

void printNumbers(int * arr, int size)
{
    for (int i = 0; i < size; i++) {
        cout << "Number " << i << " | " << arr[i] << std::endl;
    }
}

int main()
{
    int numbers[] = { 12, 2, 45, 19, 37, 8 , 5, 3, 4, 897213, 993, 23628, 7378, 3883, 88 };
    
    sort(numbers, sizeof(numbers) / sizeof(int));
    printNumbers(numbers, sizeof(numbers) / sizeof(int));
    
    return 0;
}
