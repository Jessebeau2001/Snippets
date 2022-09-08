#pragma once
#include <string>

class itime_source
{
public:
    virtual std::string get_time_s() const = 0;
    virtual ~itime_source() = default;
};
