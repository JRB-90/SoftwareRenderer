#include "Vector2D.h"
#include "Frame2D.h"
#include <cmath>

using namespace softengine;

Vector2D::Vector2D()
  :
	x(0.0),
	y(0.0)
{
}

Vector2D::Vector2D(const Vector2D& vector)
  :
	x(vector.X()),
	y(vector.Y())
{
}

Vector2D::Vector2D(
	double x, 
	double y)
  :
	x(x),
	y(y)
{
}

double Vector2D::Length()
{
	return std::sqrt(x * x + y * y);
}

void Vector2D::Normalise()
{
	double l = Length();
	if (l > 0)
	{
		x = x / l;
		y = y / l;
	}
}

Vector2D Vector2D::Normalised()
{
	Vector2D v(*this);
	v.Normalise();

	return v;
}

Vector2D Vector2D::operator+(const Vector2D& vec)
{
	return
		Vector2D(
			x + vec.X(),
			y + vec.Y()
		);
}

Vector2D Vector2D::operator-(const Vector2D& vec)
{
	return
		Vector2D(
			x - vec.X(),
			y - vec.Y()
		);
}

Vector2D Vector2D::operator*(const double scalar)
{
	return
		Vector2D(
			x * scalar,
			y * scalar
		);
}

Vector2D Vector2D::operator*(const Frame2D& frame)
{
	double res[3] = { 0, 0, 0 };

	for (size_t i = 0; i < 3; i++)
	{
		res[i] =
			x * frame.At(i, 0) +
			y * frame.At(i, 1) +
			1 * frame.At(i, 2);
	}

	return Vector2D(
		res[0],
		res[1]
	);
}

Vector2D Vector2D::operator/(const double scalar)
{
	return 
		Vector2D(
			x / scalar,
			y / scalar
		);
}
