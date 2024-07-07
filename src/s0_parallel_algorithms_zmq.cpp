#include "s0_parallel_algorithms_zmq.hpp"

#include "s0_jobs/s0_jobs_parser.hpp"
#include "s0_jobs/s0_jobs_performer.hpp"

#include <charconv>
#include <iostream>

const auto worker_thread_yield_timeout = std::chrono::milliseconds(50);

const std::string s0m4b0dY::Zmq::internal_connection_string_ = "inproc:///tmp/backend";

void s0m4b0dY::Zmq::worker_task(std::stop_token stop_token, zmq::context_t& context, int worker_id) {
	zmq::socket_t worker(context, zmq::socket_type::dealer);
	worker.connect(internal_connection_string_);
	JobPerformer jobPerformer;
	JobParser jobParser;

	while (true) {
		try {
			zmq::message_t request;

            while (true)
            {
			    auto bytes = worker.recv(request, zmq::recv_flags::dontwait);
                if (bytes) break;
                if (stop_token.stop_requested()) return;
                std::this_thread::sleep_for(worker_thread_yield_timeout);
            }

			std::string received_message(static_cast<char*>(request.data()), request.size());

			// Simulate some work
			auto job = jobParser.parseJob(received_message);
			if (job == Job::EXIT)
			{
				return;
			}
			auto reply_message = jobPerformer.performJob(job, received_message);

			zmq::message_t reply(reply_message.size());
			memcpy(reply.data(), reply_message.c_str(), reply_message.size());

			worker.send(reply, zmq::send_flags::none);
		} catch (const zmq::error_t& e) {
			std::cerr << "Error sending message: " << e.what() << std::endl;
			// Handle the error appropriately, e.g., retry, log, or exit
		}
	}
}

void s0m4b0dY::Zmq::sendMessage(std::string message)
{
	zmq::message_t request(message.size());
	memcpy(request.data(), message.c_str(), message.size());

	backend_.send(request, zmq::send_flags::none);
}

std::string s0m4b0dY::Zmq::recieveMessage()
{
	zmq::message_t reply;
	std::ignore = backend_.recv(reply, zmq::recv_flags::none);
	std::string received_reply(static_cast<char*>(reply.data()), reply.size());
	return received_reply;
}

s0m4b0dY::Zmq::Zmq(int n_threads) :
	n_threads_(n_threads),
	context_(1),
	backend_(context_, zmq::socket_type::dealer)
{
	backend_.bind(internal_connection_string_);

	for (int i = 0; i < n_threads; ++i) {
		workers_.emplace_back(worker_task, std::ref(context_), i);
		workers_.back();
	}
}

s0m4b0dY::Zmq::~Zmq()
{
	for (int i = 0; i < n_threads_; ++i) {
        workers_[i].get_stop_source().request_stop();
		workers_[i].join();
	}
}
