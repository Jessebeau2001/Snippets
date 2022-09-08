#pragma once

#include <string>
#include <iostream>
#include "ilogger.h"
#include "itime_source.h"

namespace lib{
class logger final : public loggers::ilogger {
    public:
        explicit logger(std::ostream& out);
        logger();
        void log(const std::string& msg) const override;
    
    private:
        std::ostream & m_out_;
    
        void output_time() const;
        static void set_time_src(std::unique_ptr<itime_source> source) noexcept;
        static std::unique_ptr<itime_source> t_src_;
    };
}
