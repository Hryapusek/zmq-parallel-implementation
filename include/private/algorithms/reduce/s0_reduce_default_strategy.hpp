#ifndef S0_DEFAULT_REDUCE_STRATEGY_HPP
#define S0_DEFAULT_REDUCE_STRATEGY_HPP

#include "s0_reduce_strategy_interface.hpp"

namespace s0m4b0dY
{
    class ReduceDefaultStrategy : public IReduceStrategy
    {
    public:
        std::any reduce(std::string_view message) override;
    };
}

#endif
