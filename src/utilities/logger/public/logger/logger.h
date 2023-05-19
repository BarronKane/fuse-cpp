#pragma once

#include <sstream>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

#include "utilities/platform.h"

namespace logging 
{
	class Logger
	{
	public:

		static Logger * const logger;

	private:

		Logger(void) {}
		Logger(Logger& other) {}
		Logger& operator=(Logger& other) {}
	};
}
