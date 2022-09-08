#pragma once

#include <string>
#include <iostream>
#include "ilogger.h"
#include "itext_writer.h"
#include "itime_source.h"

namespace lib{
    class logger final : public loggers::ilogger {
    public:
        logger();
        explicit logger(std::unique_ptr<writers::itext_writer> out);
        void log(const std::string_view & msg) const override;
        void set_time_src(std::unique_ptr<itime_source> source) noexcept;
    
    private:
        std::unique_ptr<writers::itext_writer> m_writer_;
        std::unique_ptr<itime_source> t_src_;
        void output_time() const;
    };
}
