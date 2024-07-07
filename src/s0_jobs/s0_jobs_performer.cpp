#include "s0_jobs/s0_jobs_performer.hpp"

#include <string>
#include <charconv>
#include <mutex>

namespace s0m4b0dY
{
std::vector<std::unique_ptr<GeneralReduceInterface> > JobPerformer::reduceImplementations_;

JobPerformer::JobPerformer()
{
	static std::mutex mutex;
	if (reduceImplementations_.empty())
	{
		std::unique_lock lock(mutex);
		if (reduceImplementations_.empty())
		{
			reduceImplementations_ = ReduceFactoryRegistry::instance().createAll();
		}
	}
}

std::string JobPerformer::performJob(Job job, std::string_view message)
{
	auto firstSemicolonPos = message.find(':');
	if (firstSemicolonPos == std::string_view::npos)
		return "";
	auto secondSemicolonPos = message.find(':', firstSemicolonPos + 1);
	if (secondSemicolonPos == std::string_view::npos)
		return "";
	auto typeName = std::string_view(message.begin() + firstSemicolonPos + 1, message.begin() + secondSemicolonPos);
	auto message_data = std::string_view(message.begin() + secondSemicolonPos + 1, message.end());
	switch (job)
	{
	case Job::REDUCE:
	{
		for (auto &reducePtr : reduceImplementations_)
		{
			if (reducePtr->canProcessType(typeName))
			{
				return reducePtr->reduce(message_data);
			}
		}
		assert(false);
		return "";
	}

	default:
		return "";
	}
}

}
