#pragma once

#include <string>
#include <vector>
#include <memory>

#include "utilities/utilities.h"
#include "logger/sink.h"
#include "logger/record.h"

namespace logging
{
	class source
	{
	public:

		source(std::string Category);
		
		void Attach_Sink(std::shared_ptr<sink>);

		void Push_Sinks(std::shared_ptr<record> in_record);

		bool b_meta = true;

	protected:

	private:

		std::vector<std::shared_ptr<sink>> sinks;

		std::string _category;	
	};
}
