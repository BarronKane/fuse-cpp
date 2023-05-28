#include "logger/sink.h"

namespace logging
{
	sink::sink(std::string file)
	{
		const std::filesystem::path in_file = file;

		file_path = in_file;
		file_check();
	}

	sink::sink(std::filesystem::path file)
	{
		file_path = file;
		file_check();
	}

	sink::~sink()
	{
		b_active = false;
		thread_writer.join();
	}

	void sink::with_header(std::string header)
	{
		file_header = header;
	}

	void sink::file_check()
	{
		std::lock_guard<std::mutex> lock(m_file);
		
		try {
			file.open(file_path);
			if (!file_header.empty())
			{
				file << file_header;
			}
			else
			{
				file << "BEGIN LOG\n";
			}
			file.close();
		}
		catch (const std::ifstream::failure& e)
		{
			std::cout << "[FATAL] CANNOT OPEN OR WRITE TO FILE FOR LOGGING: " << file_path << "\n";
			std::cout << "EXITING";
			exit(1);
		}
	}

	void sink::push(record& record)
	{
		std::lock_guard<std::mutex> lock(m_file);

	}

	void sink::print_thread()
	{
		while (b_active = true)
		{
			{
				std::lock_guard<std::mutex> lock(m_queue);
				while (!records.empty())
				{
					std::shared_ptr<record> _record = records.front();
					records.pop();

					file.open(file_path);

					if (!_record->prefix.empty())
					{
						file << _record->prefix;
					}

					file << _record->_record;

					if (!_record->postfix.empty())
					{
						file << _record->postfix;
					}
					file << "\n";

					file.close();
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}
}
