#pragma once
#include <fstream>

#include "itext_writer.h"

namespace writers
{
    struct stream_writer final : writers::itext_writer
    {
        explicit stream_writer(const char * file_name);
        itext_writer & operator<<(const std::string_view & str) override;
        itext_writer & operator<<(const char & c) override;

    private:
        std::ofstream ofs_;
    };
}

