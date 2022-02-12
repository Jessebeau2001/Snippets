/*
    Jesse inefficient as fuck sorting algorthim for cpp :)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "BruhSort.h"
#include "StreamHandler.h"

using std::cout;
using std::string;
using std::map;
using std::ifstream;

void printNumbers(int * arr, int size)
{
    for (int i = 0; i < size; i++) {
        cout << "Number " << i << " | " << arr[i] << std::endl;
    }
}

void strToLower(string & str)
{
    for (auto & c : str) {
        c = tolower(c);
    }
}

map<char, unsigned int> getCharacterMap(string str, bool setLower = false)
{
    if (setLower) strToLower(str);                                 // Didn't know whether it should only count lower case letters so added this param

    map<char, unsigned int> charMap;
    unsigned int charCount['z' - 'A']{};                           // 'z' - 'A' results in amount of characters (57) we check for

    for (auto & c : str) {
        if (std::isalpha(c)) charCount[c - 'A']++;                  // Makes sure to only include letters
    }

    for (int i = 0; i < sizeof(charCount) / sizeof(int); i++) {     // Needs to be for (i) loop cause we need the iterator as number
        charMap.insert(std::pair<char, unsigned int>('A' + i, charCount[i]));
    }

    return charMap;
}

template <typename A, typename B>
void printMap(map<A, B> tMap)                                       // I find this a beautifull function but is it really ???
{
    for (auto & item : tMap) {                                      // Same goes for this for loop
        cout << item.first << " | " << item.second << std::endl;
    }
}

int main()
{
    // int numbers[] = { 12, 2, 45, 19, 37, 8 , 5, 3, 4, 897213, 993, 23628, 7378, 3883, 88 };
    // bsrt::sort(numbers, sizeof(numbers) / sizeof(int));
    // printNumbers(numbers, sizeof(numbers) / sizeof(int));

    ifstream stream{};
    streamhandler::appendValidStream(stream);

    std::stringstream buf;
    buf << stream.rdbuf();
    string str = buf.str();
    
    // cout << str;
    printMap(getCharacterMap(str));
    
    return 0;
}
