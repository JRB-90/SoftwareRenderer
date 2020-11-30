#pragma once

#include <vector>

namespace softengine
{
	class Utils2D
	{
	public:
		Utils2D() = delete;

		static std::vector<size_t> InterpolateXPixelValues(
			size_t x0,
			size_t y0,
			size_t x1,
			size_t y1
		);

		static std::vector<size_t> InterpolateYPixelValues(
			size_t x0,
			size_t y0,
			size_t x1,
			size_t y1
		);
	};
}