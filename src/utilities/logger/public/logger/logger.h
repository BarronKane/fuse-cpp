#pragma once

#include <sstream>
#include <stdarg.h>
#include <format>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

#include "utilities/platform.h"

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

	// Not cloneable.
	Logger(Logger &other) = delete;
	// Not assignable.
	void operator=(const Logger &) = delete;

	// Static method to control access.
	static Logger* GetInstance();

	// Public Interface

	void Log(LogLevel level, std::string message);


protected:

	Logger();
	~Logger();

	static Logger* logger_;

private:

	std::mutex m_queue;
	std::mutex m_fileout;
	std::mutex m_stdout;
	std::mutex m_stderr;

	std::queue<std::string> queue;

	std::thread print_thread;
};

void Log(LogLevel level, const char* message, ...)
{
	Logger* logger = Logger::GetInstance();

	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);

	std::string msg;
	size_t len = vsnprintf(0, 0, message, args);
	msg.resize(len + 1); // For NUL.
	vsnprintf(&msg[0], len + 1, message, args);
	msg.resize(len); // Remove NUL.

	logger->Log(level, msg);
}
