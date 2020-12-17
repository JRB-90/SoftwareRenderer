#include "MathUtils.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace softengine;

double MathUtils::ToRad(double deg)
{
	return (deg * M_PI) / 180.0;
}

double MathUtils::ToDeg(double rad)
{
	return (rad * 180.0) / M_PI;
}

Vector2D MathUtils::TransformPointFor2D(
	Vector2D& position, 
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
		1.0, 0.0, transform.Translation().X(),
		0.0, 1.0, transform.Translation().Y(),
		0.0, 0.0, 1.0
	);

	return ((position * s) * r) * t;
}

int MathUtils::Interpolate(
	int val1, 
	int val2, 
	double factor)
{
	int delta = val2 - val1;

	return val1 + (int)((double)delta * factor);
}

double MathUtils::Interpolate(
	double val1,
	double val2, 
	double factor)
{
	double delta = val2 - val1;

	return val1 + (delta * factor);
}
