#ifndef S0_REDUCE_STRATEGY_INTERFACE_HPP
#define S0_REDUCE_STRATEGY_INTERFACE_HPP

#include <string_view>
#include <any>

namespace s0m4b0dY
{
    class IReduceStrategy
    {
        virtual std::any reduce(std::string_view message) = 0;
    };
}

#endif
