#include "gtest/gtest.h"

#include <ranges>
#include <vector>
#include <numeric>
#include <thread>

#include "s0_parallel_algorithms_zmq.hpp"

TEST(reduceParallelAlgo, VectorOf500Elements)
{
    auto range = std::ranges::views::iota(0, 500);
    std::vector<long long> arr(range.begin(), range.end());
    s0m4b0dY::Zmq zmq(std::thread::hardware_concurrency());
    auto result = zmq.reduce({arr.begin(), arr.end()});
    ASSERT_EQ(result, std::reduce(arr.begin(), arr.end()));
}
