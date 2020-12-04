#pragma once

#include <vector>

namespace softengine
{
	class Utils2D
	{
	public:
		Utils2D() = delete;

		static std::vector<int> InterpolateXPixelValues(
			int x0,
			int y0,
			int x1,
			int y1
		);

		static std::vector<int> InterpolateYPixelValues(
			int x0,
			int y0,
			int x1,
			int y1
		);
	};
}