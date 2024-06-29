#ifndef S0M4B0D4_PARALLEL_ALGORITHMS
#define S0M4B0D4_PARALLEL_ALGORITHMS

#include <type_traits>
#include <vector>
#include <thread>
#include <zmq.hpp>

#include "CommonUtils/s0_type_traits.hpp"
#include "CommonUtils/s0_utils.hpp"

namespace s0m4b0dY
{
  class Zmq
  {
  public:
    Zmq(int n_threads);

    template <_helpers::AddableIterator Iterator_t>
    _helpers::IteratorValueType<Iterator_t>::value_type reduce(Iterator_t begin, Iterator_t end);

    void worker_task(zmq::context_t& context, int worker_id);

  private:
    const std::string internal_connection_string_ = "ipc:///tmp/backend";
    std::vector<std::thread> workers_;
  };

  template <_helpers::AddableIterator Iterator_t>
  inline _helpers::IteratorValueType<Iterator_t>::value_type Zmq::reduce(Iterator_t begin, Iterator_t end)
  {
    using value_type = _helpers::IteratorValueType<Iterator_t>::value_type;
    const auto init_value = 0;
    std::vector<std::pair<Iterator_t, Iterator_t>> ranges = generateRanges(begin, end, 12);
    std::vector<value_type> results(ranges.size(), init_value);
    for (auto i = 0; i < ranges.size(); ++i)
    {
      const auto &range = ranges[i];
      value_type result = init_value;
      for (auto it = range.first; it != range.second; it++)
      {
        result += *it;
      }
      results[i] = result;
    }
    auto result = init_value;
    for (const auto &local_result : results)
    {
      result += local_result;
    }
    return result;
  }
} // namespace s0m4b0dY

#endif
