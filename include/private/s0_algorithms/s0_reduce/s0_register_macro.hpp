#ifndef S0_REGISTER_MACRO_HPP
#define S0_REGISTER_MACRO_HPP

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <numeric>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "s0_algorithms/s0_reduce/s0_reduce_registry.hpp"

namespace s0m4b0dY
{
    template < class T >
    constexpr const char *getTypeName(T* = nullptr) = delete;
}

#define S0M4B0DY_DEFINE_REDUCE_IMPLEMENTATION(type, typeName, className) \
class className : public s0m4b0dY::GeneralReduceInterface \
{ \
public: \
    std::string reduce(std::string_view message) override \
    { \
        auto values = deserialize(message); \
        if (values.empty()) \
            return ""; \
        return serialize(std::reduce(values.begin(), values.end())); \
    } \
private: \
    std::vector<type> deserialize(std::string_view message) \
{ \
    std::vector<type> values; \
    try \
    { \
        std::istringstream ss{std::string(message)}; \
        boost::archive::text_iarchive ar(ss, boost::archive::no_header); \
        while (true) \
        { \
            type value; \
            ar >> value; \
            values.push_back(value); \
        } \
    } \
    catch (const boost::archive::archive_exception& e) \
    { \
        if (e.code != boost::archive::archive_exception::input_stream_error) \
        { \
            throw; \
        } \
        /* Handle the end of stream situation or other specific cases if needed */ \
    } \
    return values; \
    } \
    std::string serialize(const type &value) \
    { \
        std::stringstream ss; \
        { \
            boost::archive::text_oarchive ar(ss, boost::archive::no_header); \
            ar << value; \
        } \
        return ss.str(); \
    } \
    constexpr bool canProcessType(const std::string_view &anotherTypeName) override \
    { \
        return anotherTypeName == typeName; \
    } \
}; \
namespace s0m4b0dY \
{ \
    template <> \
    constexpr const char *getTypeName<type>(type* unused) \
    { \
        return typeName; \
    } \
}

S0M4B0DY_DEFINE_REDUCE_IMPLEMENTATION(long long, "long long", ReduceImplementation_int);
S0M4B0DY_REGISTER_REDUCE_IMPLEMENTATION("long long", ReduceImplementation_int);

#endif
