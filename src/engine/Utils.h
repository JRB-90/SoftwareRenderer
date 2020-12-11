#pragma once

#include <vector>
#include <string>

namespace softengine
{
	class Utils
	{
	public:
		Utils() = delete;

		static std::vector<std::string> SplitString(
			const std::string& input, 
			char delimiter
		);
	};
}