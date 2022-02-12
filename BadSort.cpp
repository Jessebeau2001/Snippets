/*
    Jesse inefficient as fuck sorting algorthim for cpp :)
*/

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::string;
using std::map;

void swap(int &a, int &b)
{
    auto temp = a;
    a = b;
    b = temp;
}

bool sortOnce(int * arr, int size)
{
    // cout << "Do it again\n";
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
    if (size < 2) return;                       // Return when only 1 element in array.
    
    while (!sortOnce(arr, size));
}

void printNumbers(int * arr, int size)
{
    for (int i = 0; i < size; i++) {
        cout << "Number " << i << " | " << arr[i] << std::endl;
    }
}

map<char, unsigned int> createCharacterMap(string str, int size)
{
    map<char, unsigned int> myMap;
    unsigned int cCount['z' - 'A'];                 // 'z' - 'A' results in amount of letters we check for
    
    for (int c = 'A'; c < 'z'; c++) {                          // Can also use (auto & c : str) but then index has to be formula: c - 'z'
        for (auto & letter : str) {
            if(letter == c) cCount[c - 'A']++;
        }
        cout << (char) c << ": " << cCount[c- 'A'];
    }
    
    
}

int main()
{
    int numbers[] = { 12, 2, 45, 19, 37, 8 , 5, 3, 4, 897213, 993, 23628, 7378, 3883, 88 };
    
    sort(numbers, sizeof(numbers) / sizeof(int));
    printNumbers(numbers, sizeof(numbers) / sizeof(int));
    
    string scentence = "I'm a scentence. And I'm another scentence";
    
    map<char, unsigned int> charmap;
    charmap.insert(std::pair<char, unsigned int>('a', 5));
    charmap.insert(std::pair<char, unsigned int>('b', 7));
    charmap.insert(std::pair<char, unsigned int>('c', 5));
    
    for (auto & item : charmap) {
        cout << item.first << " | " << item.second << std::endl;
    }
    return 0;
}
