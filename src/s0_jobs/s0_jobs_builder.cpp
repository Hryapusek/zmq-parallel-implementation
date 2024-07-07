#include "s0_jobs/s0_jobs_builder.hpp"

#include "fmt/format.h"
#include <span>

std::string s0m4b0dY::JobBuilder::buildId(Job job)
{
    return fmt::format("{:03d}", static_cast<int>(job));
}
