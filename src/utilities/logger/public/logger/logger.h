#pragma once

#include <string>
#include <sstream>
#include <cstdarg>
#include <format>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>
#include <source_location>

#include "utilities/utilities.h"
#include "logger/source.h"

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

	void Compose(LogLevel level, std::string message);

	void Set_Source(std::string category);
	bool Check_Source_Meta();

	void shutdown();

protected:

	Logger();

	static Logger* logger_;

private:

	// Not cloneable.
	Logger(Logger& other) = delete;
	// Not assignable.
	void operator=(const Logger&) = delete;

	void Make_Source(std::string category);

	void push_cout(std::string message);

	bool b_print = true;
	void print();

	std::mutex m_queue_cout;

	std::mutex m_stdout;
	std::mutex m_stderr;

	std::map<std::string, std::unique_ptr<logging::source>> sources;
	std::string current_source;

	std::queue<std::string> cout_queue;

	std::thread print_thread;
};

template<typename... Args>
void _log(LogLevel level, const std::source_location& loc, std::string_view format, Args&&... args)
{
	Logger* logger = Logger::GetInstance();
	std::string msg = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));

	std::string final_msg;
	if (logger->Check_Source_Meta())
	{
		std::ostringstream meta;
		meta <<  loc.file_name() << ":";
		meta << loc.line() << ":";
		meta << loc.function_name() << " - ";
		final_msg = meta.str() + msg;
	}
	else
	{
		final_msg = msg;
	}

	logger->Compose(level, final_msg);
}

// MSVC is the only compiler not to support an optional comma in C++20.
#if _MSC_VER
#define Log(level, msg, ...) _log(level, std::source_location::current(), msg, __VA_ARGS__)
#else
#define Log(level, msg, ...) _log(level, std::source_location::current(), msg __VA_OPT__(,) __VA_ARGS__)
#endif
