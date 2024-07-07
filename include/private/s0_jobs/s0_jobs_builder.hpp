#ifndef S0_JOB_BUILDER_HPP
#define S0_JOB_BUILDER_HPP

#include "s0_jobs.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <sstream>

#include <vector>
#include <string>
#include <span>
#include "s0_algorithms/s0_reduce/s0_register_macro.hpp"

namespace s0m4b0dY
{
    class JobBuilder
    {
    public:
        template < class T >
        std::string createReduceRequest(const std::span<T> &values);
        std::string buildId(Job job);

    private:
        template < class Decay_t >
        std::string buildHeader(Job job, Decay_t *_unused = nullptr);
    };

    template < class T >
    std::string JobBuilder::createReduceRequest(const std::span<T> &values)
    {
        using Decay_t = std::remove_cvref_t<T>;
        std::stringstream stream;
        boost::archive::text_oarchive ar(stream, boost::archive::no_header);
        for (const auto &value : values)
        {
            ar << value;
        }
        return buildHeader<Decay_t>(Job::REDUCE) + stream.str();
    }

    template < class Decay_t >
    std::string JobBuilder::buildHeader(Job job, Decay_t *_unused)
    {
        std::string resultStr;
        resultStr += buildId(Job::REDUCE) + ":" + getTypeName<Decay_t>() + ":";
        return resultStr;
    }
}

#endif
