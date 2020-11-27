#include "Vector3D.h"

#include <cmath>

using namespace softengine;

Vector3D::Vector3D()
  :
	x(0.0),
	y(0.0),
	z(0.0)
{
}

Vector3D::Vector3D(const Vector3D& vector)
  :
	x(vector.X()),
	y(vector.Y()),
	z(vector.Z())
{
}

Vector3D::Vector3D(
	double x,
	double y,
	double z)
  :
	x(x),
	y(y),
	z(z)
{
}

double Vector3D::Length()
{
	return std::sqrt(x * x + y * y + z * z);
}

void Vector3D::Normalise()
{
	double l = Length();
	if (l > 0)
	{
		x = x / l;
		y = y / l;
		z = z / l;
	}
}

Vector3D Vector3D::Normalised()
{
	Vector3D v(*this);
	v.Normalise();

	return v;
}

Vector3D Vector3D::operator+(const Vector3D& vec)
{
	return
		Vector3D(
			x + vec.X(),
			y + vec.Y(),
			z + vec.Z()
		);
}

Vector3D Vector3D::operator-(const Vector3D& vec)
{
	return
		Vector3D(
			x - vec.X(),
			y - vec.Y(),
			z - vec.Z()
		);
}

Vector3D Vector3D::operator*(const double scalar)
{
	return
		Vector3D(
			x * scalar,
			y * scalar,
			z * scalar
		);
}

Vector3D Vector3D::operator/(const double scalar)
{
	return
		Vector3D(
			x / scalar,
			y / scalar,
			z / scalar
		);
}
