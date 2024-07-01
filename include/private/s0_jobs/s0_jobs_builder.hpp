#ifndef S0_JOB_BUILDER_HPP
#define S0_JOB_BUILDER_HPP

#include "s0_jobs.hpp"

#include <vector>
#include <string>
#include <span>

namespace s0m4b0dY
{
    class JobBuilder
    {
    public:
        std::string createReduceRequest(const std::span<const long long> &numbers);
        std::string buildId(Job job);
        std::string spanToString(const std::span<const long long> &numbers);
    };
}

#endif
