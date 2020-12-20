#pragma once

#include <vector>
#include <string>

namespace softengine
{
	class Matrix4;

	class Utils
	{
	public:
		Utils() = delete;

		static std::vector<std::string> SplitString(
			const std::string& input, 
			char delimiter
		);

		static void PrintMatrix(Matrix4 mat);
	};
}