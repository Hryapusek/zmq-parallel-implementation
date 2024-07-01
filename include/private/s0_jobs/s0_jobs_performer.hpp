#ifndef S0_JOB_PERFORMER_HPP
#define S0_JOB_PERFORMER_HPP

#include "s0_jobs/s0_jobs_parser.hpp"
#include "s0_jobs/s0_jobs_builder.hpp"


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
        std::unique_ptr<IReduceStrategy> reduceStrategy_ = nullptr;
        JobBuilder jobBuilder_;
        JobParser jobParser_;
    };
}

#endif
