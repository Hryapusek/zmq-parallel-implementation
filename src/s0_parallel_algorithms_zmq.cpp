#include "s0_parallel_algorithms_zmq.hpp"

namespace
{
    
}

void s0m4b0dY::Zmq::worker_task(zmq::context_t& context, int worker_id) {
    zmq::socket_t worker(context, zmq::socket_type::dealer);
    worker.connect(internal_connection_string_);

    while (true) {
        zmq::message_t identity;
        zmq::message_t request;

        worker.recv(identity, zmq::recv_flags::none);
        worker.recv(request, zmq::recv_flags::none);

        std::string received_message(static_cast<char*>(request.data()), request.size());

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Send reply back to client
        std::string reply_message = "World from worker " + std::to_string(worker_id);
        zmq::message_t reply(reply_message.size());
        memcpy(reply.data(), reply_message.c_str(), reply_message.size());

        worker.send(identity, zmq::send_flags::sndmore);
        worker.send(reply, zmq::send_flags::none);
    }
}

s0m4b0dY::Zmq::Zmq(int n_threads) :
    context_(1)
{
    zmq::context_t context(1);

    zmq::socket_t backend(context, zmq::socket_type::dealer);
    backend.bind(internal_connection_string_);

    const int num_workers = 5;
    std::vector<std::thread> workers;
    for (int i = 0; i < num_workers; ++i) {
        workers.emplace_back(worker_task, std::ref(context), i);
        workers.back().detach();
    }
}
