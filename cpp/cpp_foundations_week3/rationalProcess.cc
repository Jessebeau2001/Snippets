#ifndef RATIONAL_PROCESS
#define RATIONAL_PROCESS

#include <iostream>
#include <fstream>
#include <string>
#include "rational.h"

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;

class RationalProcess
{
    public:
        static bool process(ifstream & stream_in)
        {
            ofstream stream_out;
            stream_out.open("./files/out.txt");

            string line{};
            while (std::getline(stream_in, line)) {
                Rational result = Rational::calculate(line);
                stream_out << line << " = " << result.to_string() << std::endl;
            }

            return true;
        }

        static bool process(string path)
        {
            ifstream stream_in{path};
            if (stream_in.is_open() == false) return false;

            process(stream_in);
        }
};

#endif
