#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"
#include "logger/sink.h"
#include "utilities/utilities.h"

Logger* Logger::logger_;

Logger::Logger()
{
	// Default source.
	Set_Source("");
	// Default sink.
	std::filesystem::path cwd = GetEXE();
	cwd.replace_filename("log");
	cwd.replace_extension("txt");

	std::shared_ptr<logging::sink> sink(new logging::sink(cwd));
	sources[current_source]->Attach_Sink(std::move(sink));
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

void Logger::Compose(LogLevel level, std::string message)
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

	push_cout(oo.str());
		
	std::shared_ptr<logging::record> record(new logging::record(os.str()));
	sources[current_source]->Push_Sinks(std::move(record));
}

void Logger::Make_Source(std::string category)
{	
	sources.insert(std::make_pair(category, std::unique_ptr<logging::source>(new logging::source(category))));
}

void Logger::Set_Source(std::string category)
{
	if (!sources.contains(category))
	{
		Make_Source(category);
	}

	current_source = category;
}

bool Logger::Check_Source_Meta()
{
	return sources[current_source]->b_meta;
}

void Logger::push_cout(std::string message)
{
	std::lock_guard<std::mutex> lock(m_queue_cout);
	cout_queue.push(message);
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
