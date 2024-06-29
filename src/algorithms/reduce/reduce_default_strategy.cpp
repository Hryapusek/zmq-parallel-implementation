#include "algorithms/reduce/s0_reduce_default_strategy.hpp"
#include "s0_utils.hpp"
#include <numeric>


std::any s0m4b0dY::ReduceDefaultStrategy::reduce(std::string_view message)
{
    auto numbers = parseNumbersVector(message);
    return std::reduce(numbers.begin(), numbers.end());
}