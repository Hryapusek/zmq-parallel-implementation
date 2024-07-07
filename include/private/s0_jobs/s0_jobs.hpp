#ifndef S0_JOBS_HPP
#define S0_JOBS_HPP

#include <string_view>
#include <any>
#include <memory>
#include <vector>

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
