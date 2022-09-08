#include "console_writer.h"

#include <iostream>

lib::itext_writer & console_writer::operator<<(const std::string_view & str)
{
    std::cout << str;
    return *this;
}

lib::itext_writer& console_writer::operator<<(const char & c)
{
    std::cout << c;
    return *this;
}
