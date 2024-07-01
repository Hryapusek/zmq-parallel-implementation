#include "s0_jobs/s0_jobs_performer.hpp"

#include "s0_algorithms/s0_reduce/s0_reduce_default_strategy.hpp"

#include <string>
#include <charconv>

namespace s0m4b0dY
{
    JobPerformer::JobPerformer()
    {
        reduceStrategy_ = std::make_unique<ReduceDefaultStrategy>();
    }

    std::string JobPerformer::performJob(Job job, std::string_view message)
    {
        auto semicolonPos = message.find(':');
        if (semicolonPos == std::string_view::npos)
            return "";
        auto message_data = std::string_view(message.begin() + semicolonPos + 1, message.end());
        switch (job)
        {
        case Job::REDUCE:
        {
            auto result = reduceStrategy_->reduce(jobParser_.parseNumbersVector(message_data));
            return std::to_string(result);
            break;
        }
        
        default:
            return "";
        }
    }

}
