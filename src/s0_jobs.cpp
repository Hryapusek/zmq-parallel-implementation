#include "s0_jobs.hpp"

#include "algorithms/reduce/s0_reduce_default_strategy.hpp"

#include <string>
#include <charconv>

namespace s0m4b0dY
{
    Job JobParser::parseJob(std::string_view message)
    {
        if (message.size() < 3)
            return Job::INVALID;

        auto jobIdStr = std::string_view(message.begin(), message.begin()+2);
        int jobId = 0;
        auto result = std::from_chars(jobIdStr.data(), jobIdStr.data() + jobIdStr.size(), jobId);

        if (result.ec == std::errc::invalid_argument)
            return Job::INVALID;

        if (jobId < 0 or jobId > static_cast<int>(Job::MAX))
            return Job::INVALID;

        return Job(jobId);
    }

    JobPerformer::JobPerformer()
    {
        reduceStrategy_ = std::make_unique<ReduceDefaultStrategy>();
    }

    std::any JobPerformer::performJob(Job job, std::string_view message)
    {
        auto semicolonPos = message.find(':');
        if (semicolonPos == std::string_view::npos)
            return std::any();
        auto message_data = std::string_view(message.begin() + semicolonPos + 1, message.end());
        switch (job)
        {
        case Job::REDUCE:
            return reduceStrategy_->reduce(message_data);
            break;
        
        default:
            return std::any();
        }
    }

}
