#ifndef S0_REDUCE_STRATEGY_INTERFACE_HPP
#define S0_REDUCE_STRATEGY_INTERFACE_HPP

#include <span>

namespace s0m4b0dY
{
    class IReduceStrategy
    {
    public:
        /**
         * @param message should contain only data with numbers separated with whitespaces
         */
        virtual long long reduce(const std::span<const long long> &numbers) = 0;
    };
}

#endif
