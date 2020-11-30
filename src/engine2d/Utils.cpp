#include "Utils2D.h"

using namespace softengine;

std::vector<size_t> Utils2D::InterpolateXPixelValues(
	size_t x0,
	size_t y0,
	size_t x1,
	size_t y1)
{
	return InterpolateYPixelValues(y0, x0, y1, x1);
}

std::vector<size_t> Utils2D::InterpolateYPixelValues(
	size_t x0,
	size_t y0,
	size_t x1,
	size_t y1)
{
	std::vector<size_t> pixels;

	if (x0 == x1)
	{
		pixels.push_back(x0);

		return pixels;
	}

	double grad = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
	double d = (double)y0;

	for (size_t i = x0; i <= x1; i++)
	{
		pixels.push_back((size_t)d);
		d += grad;
	}

	return pixels;
}
