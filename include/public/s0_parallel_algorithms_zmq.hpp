#ifndef S0M4B0D4_PARALLEL_ALGORITHMS
#define S0M4B0D4_PARALLEL_ALGORITHMS

#include <type_traits>
#include <vector>
#include <thread>
#include <charconv>
#include <zmq.hpp>
#include <span>

#include "CommonUtils/s0_type_traits.hpp"
#include "CommonUtils/s0_utils.hpp"

#include "s0_jobs/s0_jobs_builder.hpp"
#include "s0_jobs/s0_jobs_parser.hpp"

namespace s0m4b0dY
{
  class Zmq
  {
  public:
    Zmq(int n_threads);
    virtual ~Zmq();

    template < class T >
    long long reduce(std::span<const T> arr);

  private:
    static const std::string internal_connection_string_;
    int n_threads_;
    zmq::context_t context_;
    zmq::socket_t backend_;
    std::vector<std::jthread> workers_;
    JobBuilder jobBuilder_;
    JobParser jobParser_;

    static void worker_task(std::stop_token stop_token, zmq::context_t& context, int worker_id);
    void sendMessage(std::string message);
    std::string recieveMessage();
  };

  template < class T >
  long long s0m4b0dY::Zmq::reduce(std::span<const T> arr)
  {
    const auto init_value = 0;
    auto ranges = generateRanges(arr.begin(), arr.end(), n_threads_);
    for (auto i = 0; i < ranges.size(); ++i)
    {
      const auto &range = ranges[i];
      auto requestMessage = jobBuilder_.createReduceRequest(arr);
      sendMessage(requestMessage);
    }
    auto result = init_value;
    for (auto i = 0; i < ranges.size(); ++i)
    {
      auto reply = recieveMessage();
      long long local_result;
      auto conv_result = std::from_chars(reply.data(), reply.data() + reply.size(), local_result);

      assert(conv_result.ec != std::errc::invalid_argument);
      result += local_result;
    }
    return result;
  }

} // namespace s0m4b0dY

#endif
