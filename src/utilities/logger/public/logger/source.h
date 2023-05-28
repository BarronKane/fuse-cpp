#pragma once

#include <string>

#include "utilities/utilities.h"

namespace logging
{
	class source
	{
	public:

		source(std::string Category);

	protected:

	private:

		std::string _category;	
	};
}
