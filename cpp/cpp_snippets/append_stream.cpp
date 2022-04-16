// File appender

#include <iostream>
#include <fstream>
#include <string>

std::ifstream append_stream()
{
    std::ifstream stream{};
    std::string path{};

    std::cout << "Please enter a valid file path: ";
    getline(std::cin, path);
    while ((stream = std::ifstream{path}).is_open() == false) {
        std::cout << "file '"<< path << "' could not be found, please try again: ";
        getline(std::cin, path);
    }

    std::cout << "Opening '" << path << "'" << std::endl;
    return stream;
}
