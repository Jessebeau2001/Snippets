#include "stream_writer.h"

#include <iostream>

writers::stream_writer::stream_writer(const char * const file_name)
{
    ofs_.open(file_name);
    if (!ofs_.is_open()) ofs_.open("default.txt");
}

writers::itext_writer & writers::stream_writer::operator<<(const std::string_view& str)
{
    ofs_ << str;
    return *this;
}

writers::itext_writer & writers::stream_writer::operator<<(const char & c)
{
    ofs_ << c;
    return *this; // TODO: Q? Is this okay, this doesn't seem okay...
}
