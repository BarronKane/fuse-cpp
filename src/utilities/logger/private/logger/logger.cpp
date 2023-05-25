#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"

Logger* Logger::logger_;

Logger::Logger()
{
}

Logger* Logger::GetInstance()
{
	if (logger_ == nullptr)
	{
		logger_ = new Logger();
		logger_->print_thread = std::thread(&Logger::print, logger_);

		std::cout << "Logger Initialized." << std::endl;
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

	push_cout(os.str());
	//push_cout(os.str());
}

void Logger::push_cout(std::string message)
{
	std::lock_guard<std::mutex> lock(m_queue_cout);
	cout_queue.push(message);
	// Guard is released out of scope.
}

void Logger::print()
{
	Logger* logger = GetInstance();
	while (logger->b_print == true)
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

void Logger::shutdown()
{
	b_print = false;
	print_thread.join();
}
