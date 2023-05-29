#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>
#include <mutex>
#include <queue>
#include <thread>

#include "logger/record.h"

namespace logging
{
	class sink
	{
	public:

		sink(std::filesystem::path file);
		~sink();

		void with_header(std::string header);

		void push(std::shared_ptr<record> in_record);

	protected:

	private:

		void file_check();

		std::string file_header;
		std::filesystem::path file_path;
		std::ofstream file;

		bool b_active = true;
		void print_thread();
		
		std::mutex m_queue;
		std::mutex m_file;
		std::thread thread_writer;

		std::queue<std::shared_ptr<record>> records;
	};
}
