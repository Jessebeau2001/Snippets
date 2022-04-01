#include "utils.h"

#include <iostream>
#include <string>

namespace utils
{
    std::ifstream appendValidStream()
    {
        std::ifstream stream{};
        std::string path{};

        std::cout << "Please enter a valid file path: ";
        std::getline(std::cin, path);
        if (path == "") quit();                            // I don't like this line being here twice, also don't want to split this function :()
        stream = std::ifstream{path};

        while (stream.is_open() == false) {
            stream = std::ifstream{path};
            if (path == "") quit();
            std::cout << "file '"<< path << "' could not be found, please try again: ";
            std::getline(std::cin, path);
        }

        std::cout << "Opening '" << path << "'" << std::endl;
        return stream;
    }
    
    // Updated function for appending stream, this one is imo way cleaner than the one above
    //ifstream append_stream()
    // {
    //     ifstream stream{};
    //     string path{};

    //     cout << "Please enter a valid file path: ";
    //     getline(cin, path);

    //     while ((stream = ifstream{path}).is_open() == false) {      // Is this good, idk, I like this xD
    //         cout << "file '"<< path << "' could not be found, please try again: ";
    //         getline(cin, path);
    //     }

    //     cout << "Opening '" << path << "'" << std::endl;
    //     return stream;
    // }

    int parseInt()
    {
        int n;
        while (!(std::cin >> n)) {
            std::cin.clear();
            std::string line;
            std::getline(std::cin, line);
            std::cout << line << " is not a number" << std::endl;
        }
        return n;
    }

    void quit()
    {
        std::cout << "Exiting program, bye!";
        exit(0);
    }
}
