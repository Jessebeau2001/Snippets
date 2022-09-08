//
// Created by dza02 on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include <iostream>
#include <memory>
#include "system_time_source.h"

namespace {
    [[maybe_unused]] auto _ = [] () noexcept {
        std::ios_base::sync_with_stdio(false);
        return true;
    }();
}

int main(){
    auto log = std::make_unique<lib::logger>( );
    program prog{ std::move(log) };
    prog.run();
}