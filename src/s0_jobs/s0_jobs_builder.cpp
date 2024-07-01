#include "s0_jobs/s0_jobs_builder.hpp"

#include "fmt/format.h"
#include <span>

std::string s0m4b0dY::JobBuilder::createReduceRequest(const std::span<const long long> &numbers)
{
    std::string resultStr;
    resultStr += buildId(Job::REDUCE) + ":";
    auto span = std::span(numbers.begin(), numbers.end());
    resultStr += spanToString(span);
    return resultStr;
}

std::string s0m4b0dY::JobBuilder::buildId(Job job)
{
    return fmt::format("{:03d}", static_cast<int>(job));
}

std::string s0m4b0dY::JobBuilder::spanToString(const std::span<const long long> &numbers)
{
    std::string resultStr;
    for (auto i = 0; i < numbers.size(); i++)
    {
        resultStr += std::to_string(numbers[i]);
        if (i != numbers.size() - 1)
            resultStr += " ";
    }
    return resultStr;
}
