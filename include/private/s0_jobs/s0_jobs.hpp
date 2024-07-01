#ifndef S0_JOBS_HPP
#define S0_JOBS_HPP

#include <string_view>
#include <any>
#include <memory>
#include <vector>

#include "s0_algorithms/s0_reduce/s0_reduce_strategy_interface.hpp"

namespace s0m4b0dY
{
    enum class Job
    {
        REDUCE,
        EXIT,
        INVALID,
        MAX=INVALID
    };
}

#endif
