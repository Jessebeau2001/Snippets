/*
    Jesse inefficient as fuck text countint and sorting programme for cpp :)
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <map>

#include "BruhSort.h"           // Bruh sort is unused but I wrote it so wanted to include it.
#include "StreamHandler.h"
#include "Utils.h"

using std::ifstream;
using std::stringstream;
using std::string;
using std::map;

int main()
{
    ifstream stream{};
    streamhandler::appendValidStream(stream);

    stringstream buf;
    buf << stream.rdbuf();
    string str = buf.str();
    
    auto mp = utils::getCharacterMap(str, true);
    utils::printMapSorted(mp);
    return 0;
}
