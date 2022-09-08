#pragma once
#include "itime_source.h"

class system_time_source final : public itime_source
{
public:
    std::string get_time_s() const override;
};
