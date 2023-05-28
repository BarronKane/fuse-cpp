#pragma once

#include <string>

namespace logging
{
	/**
	* Having a dedicated record class will make composition far more intricate.
	* For now, however, this will be a simple proxy for the logging interfce.
	*/
	class record
	{
	public:

		record(std::string record);

		std::string prefix;
		std::string _record;
		std::string postfix;

	protected:

	private:

	};
}
