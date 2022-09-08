#pragma once

#include "itext_writer.h"

struct console_writer final : writers::itext_writer
{
    itext_writer & operator<<(const std::string_view & str) override;
    itext_writer & operator<<(const char& c) override;
};
