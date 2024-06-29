#ifndef S0_JOBS_HPP
#define S0_JOBS_HPP

#include <string_view>
#include <any>

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
        /**
        * @param job must be valid job
        */
        std::any performJob(Job job, std::string_view message);
    
    private:
    };
}

#endif
