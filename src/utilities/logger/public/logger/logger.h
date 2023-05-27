#pragma once

#include <string>
#include <sstream>
#include <cstdarg>
#include <format>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

#include "utilities/utilities.h"

class Logger;

enum class LogLevel : uint8
{
	verbose,
	info,
	warning,
	error,
	fatal
};

const char* LevelToString(LogLevel level) noexcept
{
	switch (level)
	{
		case LogLevel::verbose: return "VERBOSE";
		case LogLevel::info: return "INFO";
		case LogLevel::warning: return "WARNING";
		case LogLevel::error: return "ERROR";
		case LogLevel::fatal: return "FATAL";
		default: return "";
	}
}	

class Logger
{
public:

	// Static method to control access.
	static Logger* GetInstance();

	// Public Interface

	void Log(LogLevel level, std::string message);

	void shutdown();

protected:

	Logger();

	static Logger* logger_;

private:

	// Not cloneable.
	Logger(Logger& other) = delete;
	// Not assignable.
	void operator=(const Logger&) = delete;


	void push_cout(std::string message);

	bool b_print = true;
	void print();

	std::mutex m_queue_cout;
	std::mutex m_queue_file;

	std::mutex m_fileout;
	std::mutex m_stdout;
	std::mutex m_stderr;

	std::queue<std::string> cout_queue;
	std::queue<std::string> file_queue;

	std::thread print_thread;
	std::thread file_thread;
};

template<typename... Args>
void Log(LogLevel level, std::string_view format, Args&&... args)
{
	Logger* logger = Logger::GetInstance();

	logger->Log(level, std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
}

/*
void Log(LogLevel level, const char* const message, ...)
{
	Logger* logger = Logger::GetInstance();

	// This could be something else, but vector is safe.
	std::vector<char> msg = std::vector<char>{};
	size_t length = strlen(message);
	std::va_list args;
	
	// TODO: Need a way to dynamically catch the size of all argument values.
	// For now we will simple have a length a bit long.
	msg.resize(length + 200);

	va_start(args, message);
	const int status = std::vsnprintf(msg.data(), msg.size(), message, args);
	va_end(args);

	if (status < 0)
	{
		throw std::runtime_error{ "Log String Format Error." };
	}			

	logger->Log(level, std::string { msg.data() } );
}
*/
