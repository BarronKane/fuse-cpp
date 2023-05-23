#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"

Logger* Logger::logger_;

Logger::Logger()
{
	print_thread = std::thread(&Logger::print, this);
}

Logger::~Logger()
{
	print_thread.join();
	if (logger_ != nullptr)
	{
		delete logger_;
	}
}

Logger* Logger::GetInstance()
{
	if (logger_ == nullptr)
	{
		logger_ = new Logger();
	}
	return logger_;
}

void Logger::Log(LogLevel level, std::string message)
{
	std::ostringstream os;
	std::ostringstream oo;

	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

	os	<< "[" << LevelToString(level) << "] "
		<< (now->tm_year + 1900) << "-"
		<< now->tm_mon << "-"
		<< now->tm_mday
		<< " < "
		<< message;

	oo	<< "[" << LevelToString(level) << "] <"
		<< message
		<< ">";

	// Test
	//std::cout << os.str() << std::endl;

	push(oo.str(), cout_queue, m_queue_cout);
	push(os.str(), file_queue, m_queue_file);
}

void Logger::push(std::string message, std::queue<std::string> queue, std::mutex &mut)
{
	std::lock_guard<std::mutex> lock(mut);
	queue.push(message);
	// Guard is released out of scope.
}

void Logger::print()
{
	Logger* logger = GetInstance();
	while (true)
	{
		{
			std::lock_guard<std::mutex> lock(logger->m_queue_cout);
			while (!logger->cout_queue.empty())
			{
				std::cout << logger->cout_queue.front() << std::endl;
				logger->cout_queue.pop();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
