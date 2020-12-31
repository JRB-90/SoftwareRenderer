#pragma once

#include <vector>
#include <string>

namespace softengine
{
	class FileUtils
	{
	public:
		FileUtils() = delete;

		static std::vector<std::string> explode(
			const std::string& s,
			char c
		);
	};
}