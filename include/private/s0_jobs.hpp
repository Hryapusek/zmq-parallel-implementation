#ifndef S0_JOBS_HPP
#define S0_JOBS_HPP

#include <string_view>
#include <any>
#include <memory>

#include "algorithms/reduce/s0_reduce_strategy_interface.hpp"

namespace s0m4b0dY
{
    enum class Job
    {
        REDUCE,
        INVALID,
        MAX=REDUCE
    };

    class JobParser
    {
    public:
        Job parseJob(std::string_view message);
    };

    class JobPerformer
    {
    public:
        JobPerformer();
        /**
        * @param job must be valid job
        */
        std::any performJob(Job job, std::string_view message);
    
    private:
        std::unique_ptr<IReduceStrategy> reduceStrategy_ = nullptr;
    };
}

#endif
