#include "s0_jobs/s0_jobs.hpp"

#include "s0_jobs/s0_jobs_parser.hpp"

#include <string>
#include <charconv>
#include <sstream>

namespace s0m4b0dY
{
    Job JobParser::parseJob(std::string_view message)
    {
        if (message.size() < 3)
            return Job::INVALID;

        auto jobIdStr = std::string_view(message.begin(), message.begin()+3);
        int jobId = 0;
        auto result = std::from_chars(jobIdStr.data(), jobIdStr.data() + jobIdStr.size(), jobId);

        if (result.ec == std::errc::invalid_argument)
            return Job::INVALID;

        if (jobId < 0 or jobId > static_cast<int>(Job::MAX))
            return Job::INVALID;

        return Job(jobId);
    }

    std::vector<long long> s0m4b0dY::JobParser::parseNumbersVector(std::string_view message)
    {
        auto messageStr = std::string(message);
        std::istringstream ss(messageStr);
        std::vector<long long> numbers;
        std::copy(std::istream_iterator<long long>(ss), std::istream_iterator<long long>(), std::back_inserter(numbers));
        return numbers;
    }
}
