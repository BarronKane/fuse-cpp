#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"

Logger* Logger::logger_;

Logger::Logger()
{

}

Logger::~Logger()
{
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
	std::cout << os.str() << std::endl;
}
