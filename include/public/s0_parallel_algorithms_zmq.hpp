#ifndef S0M4B0D4_PARALLEL_ALGORITHMS
#define S0M4B0D4_PARALLEL_ALGORITHMS

#include <type_traits>
#include <vector>
#include <thread>
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

    long long reduce(const std::span<const long long> &arr);

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
} // namespace s0m4b0dY

#endif
