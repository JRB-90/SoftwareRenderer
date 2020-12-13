#include "Utils2D.h"

#include "MathUtils.h"
#include <cmath>

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

Vertex2D Utils2D::TransformVertexFor2D(
	Vertex2D& vertex, 
	Frame2D& transform)
{
	double angleRad = MathUtils::ToRad(transform.Angle());

	Frame2D s(
		transform.Scale().X(), 0, 0,
		0, transform.Scale().Y(), 0,
		0, 0, 1.0
	);

	Frame2D r(
		std::cos(angleRad), -std::sin(angleRad), 0.0,
		std::sin(angleRad), std::cos(angleRad), 0.0,
		0, 0, 1.0
	);

	Frame2D t(
		1.0, 0.0, transform.Position().X(),
		0.0, 1.0, transform.Position().Y(),
		0.0, 0.0, 1.0
	);

	return 
		Vertex2D(
			((vertex.Position * s) * r) * t,
			vertex.UVCoord,
			vertex.VertColor
		);
}
