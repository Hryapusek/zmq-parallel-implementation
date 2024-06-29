#include "s0_utils.hpp"

#include <sstream>
#include <iterator>
#include <numeric>


std::vector<long long> s0m4b0dY::parseNumbersVector(std::string_view message)
{
    auto messageStr = std::string(message);
    std::istringstream ss(messageStr);
    std::vector<long long> numbers;
    std::copy(std::istream_iterator<long long>(ss), std::istream_iterator<long long>(), std::back_inserter(numbers));
    return numbers;
}