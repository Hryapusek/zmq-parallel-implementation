#ifndef S0_GENERAL_REDUCE_INTERFACE_HPP
#define S0_GENERAL_REDUCE_INTERFACE_HPP

#include <string>
#include <string_view>
#include <vector>

namespace s0m4b0dY
{
class GeneralReduceInterface
{
public:
	virtual std::string reduce(std::string_view message) = 0;
	virtual bool canProcessType(const std::string_view &typeName) = 0;
};
}

#endif
