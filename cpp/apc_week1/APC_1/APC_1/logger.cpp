// ReSharper disable once CppInconsistentNaming
#define _CRT_SECURE_NO_WARNINGS  // NOLINT(bugprone-reserved-identifier)

#include "logger.h"
#include "system_time_source.h"

namespace lib{

    logger::logger(std::ostream& m_out) : m_out_(m_out) {}

    logger::logger(): logger(std::cout) {}

    void logger::log(const std::string& msg) const{
        m_out_ << '[' << t_src_->get_time_s() << "]: " << msg << '\n';
    }

    void logger::output_time() const
    {
        m_out_ << t_src_->get_time_s();
    }

    void logger::set_time_src(std::unique_ptr<itime_source> source) noexcept
    {
        t_src_ = std::move(source);
    }

    std::unique_ptr<itime_source> logger::t_src_ = std::make_unique<system_time_source>();
    // TODO: Q? Example used std::move, I like this, is that OK?
}
