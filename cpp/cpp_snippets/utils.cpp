#include "utils.h"

#include <iostream>

namespace utils
{
    std::ifstream appendValidStream()
    {
        std::ifstream stream{};
        std::string path{};
        std::cout << "Please enter a valid file path: ";
        std::cin >> path;

        while (stream.is_open() == false) {
            stream = std::ifstream{path};
            std::cout << "file '"<< path << "' could not be found, please try again: ";
            std::cin >> path;
        }

        return stream;
    }
}
