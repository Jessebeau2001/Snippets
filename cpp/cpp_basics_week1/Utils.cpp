#include "Utils.h"

namespace utils
{
    void strToLower(string & str)
    {
        for (auto & c : str) {
            c = tolower(c);
        }
    }

    // Wanted to rewrite this at some point but it works so.
    map<char, unsigned int> getCharacterMap(string & str, bool setLower)
    {
        if (setLower) strToLower(str);

        map<char, unsigned int> charMap;
        unsigned int charCount['z' - 'A']{};

        for (auto & c : str) {
            if (std::isalpha(c)) charCount[c - 'A']++;
        }

        for (int i = 0; i < sizeof(charCount) / sizeof(int); i++) {
            charMap.insert(pair<char, unsigned int>('A' + i, charCount[i]));
        }

        return charMap;
    }

    template <typename A, typename B>
    void printMap(map<A, B> mp)
    {
        for (auto & item : mp) {
            cout << item.first << " | " << item.second << endl;
        }
    }

    void printMapSorted(map<char, unsigned int> & mp)
    {
        auto vec = mapToVec(mp);

        sort(begin(vec), end(vec),
        [](const pair<char, unsigned int> & pairA, const pair<char, unsigned int> & pairB) {
            return pairA.second > pairB.second;
        });

        for (auto i : vec) {
            cout << i.first << " | " << i.second << endl;
        }
    }

    template <typename A, typename B>
    vector<pair<A, B>> mapToVec(map<A, B> mp)
    {
        vector<pair<A, B>> vec;

        for (auto & item : mp) {
            vec.push_back(pair<A, B>(item.first, item.second));
        }

        return vec;
    }
}