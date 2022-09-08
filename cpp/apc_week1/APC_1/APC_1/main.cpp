//
// Created by dza02 on 9/5/2021.
//

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

int main(){
    auto out = std::make_unique<writers::stream_writer>("my_file.txt");
    auto log = std::make_unique<lib::logger>(std::move(out));
    program prog{ std::move(log) };
    prog.run();
}