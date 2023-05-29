#include "logger/source.h"

namespace logging
{
	source::source(std::string Category)
	{
		_category = Category;
	}

	void source::Attach_Sink(std::shared_ptr<sink> in_sink)
	{
		sinks.push_back(in_sink);
	}

	void source::Push_Sinks(std::shared_ptr<record> in_record)
	{
		in_record->prefix = "[" + _category + "] ";

		if (b_meta)
		{
			
		}

		for (std::shared_ptr<sink> i : sinks)
		{
			i->push(in_record);
		}
	}
}
