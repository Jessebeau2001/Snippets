// ReSharper disable once CppInconsistentNaming
#define _CRT_SECURE_NO_WARNINGS  // NOLINT(bugprone-reserved-identifier)

#include "logger.h"

#include "console_writer.h"
#include "system_time_source.h"

namespace lib {
    logger::logger()
        : m_writer_(std::make_unique<console_writer>()), t_src_(std::make_unique<system_time_source>()) { }

    logger::logger(std::unique_ptr<writers::itext_writer> out)
        : m_writer_(std::move(out)), t_src_(std::make_unique<system_time_source>()) { }

    void logger::log(const std::string_view & msg) const
    {
        output_time();
        *m_writer_ << msg << '\n';
    }

    void logger::output_time() const
    {
        *m_writer_ << '[' << t_src_->get_time_s() << "]: ";
    }

    void logger::set_time_src(std::unique_ptr<itime_source> source) noexcept
    {
        t_src_ = std::move(source);
    }
    
    // TODO: Q? Example used std::move, I like this, is that OK?
}
