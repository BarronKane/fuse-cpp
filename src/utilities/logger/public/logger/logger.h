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
