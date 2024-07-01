#include "s0_algorithms/s0_reduce/s0_reduce_default_strategy.hpp"

#include <numeric>
#include <any>


long long s0m4b0dY::ReduceDefaultStrategy::reduce(const std::span<const long long> &numbers)
{
    return std::reduce(numbers.begin(), numbers.end());
}