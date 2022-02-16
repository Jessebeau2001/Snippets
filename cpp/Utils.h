#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using std::map;
using std::pair;
using std::vector;
using std::string;
using std::endl;
using std::sort;
using std::cout;

namespace utils
{
    static void strToLower(string & str);
    
    map<char, unsigned int> getCharacterMap(string & str, bool setLower); // I want this to be static but for some reason it doesn't let met make it static
    template <typename A, typename B>
    static void printMap(map<A, B> mp);
    void printMapSorted(map<char, unsigned int> & mp);                    // Same static genenigans for this.

    template <typename A, typename B>
    static vector<pair<A, B>> mapToVec(map<A, B> mp);
}

#endif