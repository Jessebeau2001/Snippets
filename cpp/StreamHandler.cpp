#include "StreamHandler.h"

namespace streamhandler
{
    void appendValidPath(string * path)
    {
        string newPath = "";
        while (isTextPath(newPath) == false) { //Can also use std:ifstream input.is_open();
            cout << "Please enter a valid filepath: ";
            cin >> newPath;
        }
        *path = newPath;
    }

    void appendValidStream(std::ifstream &file)
    {
        string path{};
        cout << "Please enter a valid file path: ";
        cin >> path;

        while(isStream(file, path) == false) {
            cout << "file '"<< path << "' could not be found, please try again: ";
            cin >> path;
        }

        cout << "successfully opened file '" << path << "'" << std::endl;
    }

    bool isTextPath(string path)
    {
        string extention = ".txt";
        if (path.length() < extention.length()) return false;
        if (path.substr(path.length() - 4, path.length()) == extention) return true;
        return false;
    }

    bool isStream(std::ifstream &file, string path)
    {
        file = std::ifstream{path};
        return file.is_open();
    }
}