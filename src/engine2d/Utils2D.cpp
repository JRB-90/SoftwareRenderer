#include "Utils2D.h"

using namespace softengine;

std::vector<int> Utils2D::InterpolateXPixelValues(
	int x0,
	int y0,
	int x1,
	int y1)
{
	return InterpolateYPixelValues(y0, x0, y1, x1);
}

std::vector<int> Utils2D::InterpolateYPixelValues(
	int x0,
	int y0,
	int x1,
	int y1)
{
	std::vector<int> pixels;

	if (x0 == x1)
	{
		pixels.push_back(x0);

		return pixels;
	}

	double grad = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
	double d = (double)y0;

	for (int i = x0; i <= x1; i++)
	{
		pixels.push_back(d);
		d += grad;
	}

	return pixels;
}
