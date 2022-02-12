#ifndef STREAMHANDLER_H
#define STREAMHANDLER_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::cin;

namespace streamhandler
{
    void appendValidPath(string * path);
    void appendValidStream(std::ifstream &file);

    bool isTextPath(string path);
    bool isStream(std::ifstream &file, string path);
}

#endif
