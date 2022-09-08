#pragma once

namespace loggers {
    class ilogger {
    public:
        virtual void log(const std::string_view & msg) const = 0;
        virtual ~ilogger() = default;
    };
}
