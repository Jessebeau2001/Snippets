#pragma once
#include <string_view>

namespace lib
{
    struct itext_writer
    {
        itext_writer() = default;
        virtual itext_writer & operator<< (const std::string_view & str) = 0;
        virtual itext_writer & operator<< (const char & c) = 0;
        virtual ~itext_writer() = default;
        
    };
}
