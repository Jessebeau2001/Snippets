#include "logger.h"
#include "program.h"
#include <memory>

#include "stream_writer.h"

namespace {
    [[maybe_unused]] auto _ = [] () noexcept {
        std::ios_base::sync_with_stdio(false);
        return true;
    }();
}

/*
    Name: Jesse Visscher
    Std. Nr.: 477473
    Class: ETI2V.B
*/

int main(){
    auto out = std::make_unique<writers::stream_writer>("my_file.txt"); // Init the writer
    auto log = std::make_unique<lib::logger>(std::move(out));                   // Init the logger
    // Setting time source not necessary because this already happens in the default and out stream constructor
    // However it is possible to change the time source by calling logger::set_time_src(src)

    program prog{ std::move(log) };
    prog.run();
}