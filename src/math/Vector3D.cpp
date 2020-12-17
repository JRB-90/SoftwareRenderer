#include "Vector3D.h"
#include "Frame3D.h"
#include "MathUtils.h"
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

double Vector3D::Dot(Vector3D& vec)
{
	return x * vec.X() + y * vec.Y() + z * vec.Z();
}

double Vector3D::AngleWith(Vector3D& vec)
{
	Vector3D v1 = this->Normalised();
	Vector3D v2 = vec.Normalised();
	double angle = std::acos(v1.Dot(v2)) / v1.Length() * v2.Length();

	return MathUtils::ToDeg(angle);
}

Vector3D Vector3D::Cross(Vector3D& vec)
{
	return
		Vector3D(
			y * vec.Z() - z * vec.Y(),
			z * vec.X() - x * vec.Z(),
			x * vec.Y() - y * vec.X()
		);
}

double Vector3D::AngleBetween(Vector3D& v1, Vector3D& v2)
{
	return v1.AngleWith(v2);
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

Vector3D Vector3D::operator*(const Frame3D& frame)
{
	double res[3] = { 0, 0, 0 };

	for (size_t i = 0; i < 3; i++)
	{
		res[i] =
			x * frame.At(i, 0) +
			y * frame.At(i, 1) +
			z * frame.At(i, 2) +
			1 * frame.At(i, 3);
	}

	return 
		Vector3D(
			res[0],
			res[1],
			res[2]
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
