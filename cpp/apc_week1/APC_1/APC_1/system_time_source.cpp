// ReSharper disable once CppInconsistentNaming
#define _CRT_SECURE_NO_WARNINGS  // NOLINT(clang-diagnostic-unused-macros, bugprone-reserved-identifier)

#include "system_time_source.h"
#include <chrono>
#include <iomanip>
#include <sstream>

// Returns the current system time in HH:MM:SS as string
std::string system_time_source::get_time_s() const
{
    const auto current = std::chrono::system_clock::now();
    const auto current_t = std::chrono::system_clock::to_time_t(current);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&current_t), "%X");  // NOLINT(concurrency-mt-unsafe)
    return ss.str();
}
