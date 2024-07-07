#ifndef S0_JOB_PERFORMER_HPP
#define S0_JOB_PERFORMER_HPP

#include "s0_jobs/s0_jobs_parser.hpp"
#include "s0_jobs/s0_jobs_builder.hpp"

#include "s0_algorithms/s0_reduce/s0_reduce_registry.hpp"


namespace s0m4b0dY
{
    class JobPerformer
    {
    public:
        JobPerformer();
        /**
        * @param job must be valid job
        */
        std::string performJob(Job job, std::string_view message);
    
    private:
        JobBuilder jobBuilder_;
        JobParser jobParser_;
        static std::vector<std::unique_ptr<GeneralReduceInterface>> reduceImplementations_;
    };
}

#endif
