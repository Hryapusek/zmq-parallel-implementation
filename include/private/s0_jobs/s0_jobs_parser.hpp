#ifndef S0_JOB_PARSER_HPP
#define S0_JOB_PARSER_HPP

#include "s0_jobs.hpp"

#include <vector>

namespace s0m4b0dY
{
    class JobParser
    {
    public:
        Job parseJob(std::string_view message);
        /**
         * @deprecated Do not use this
         */
        std::vector<long long> parseNumbersVector(std::string_view message);
    };
}

#endif
