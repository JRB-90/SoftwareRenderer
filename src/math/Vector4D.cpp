#include "Vector4D.h"

#include "Matrix4.h"
#include <cmath>

using namespace softengine;

Vector4D::Vector4D()
  :
	x(0.0),
	y(0.0),
	z(0.0),
	w(0.0)
{
}

Vector4D::Vector4D(const Vector4D& vector)
  :
	x(vector.X()),
	y(vector.Y()),
	z(vector.Z()),
	w(vector.W())
{
}

Vector4D::Vector4D(
	double x,
	double y,
	double z,
	double w)
  :
	x(x),
	y(y),
	z(z),
	w(w)
{
}

double Vector4D::Length()
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

void Vector4D::Normalise()
{
	double l = Length();
	if (l > 0)
	{
		x = x / l;
		y = y / l;
		z = z / l;
		w = w / l;
	}
}

Vector4D Vector4D::Normalised()
{
	Vector4D v(*this);
	v.Normalise();

	return v;
}

Vector4D Vector4D::operator+(const Vector4D& vec)
{
	return
		Vector4D(
			x + vec.X(),
			y + vec.Y(),
			z + vec.Z(),
			w + vec.W()
		);
}

Vector4D Vector4D::operator-(const Vector4D& vec)
{
	return
		Vector4D(
			x - vec.X(),
			y - vec.Y(),
			z - vec.Z(),
			w - vec.W()
		);
}

Vector4D Vector4D::operator*(const double scalar)
{
	return
		Vector4D(
			x * scalar,
			y * scalar,
			z * scalar,
			w * scalar
		);
}

Vector4D Vector4D::operator*(const Matrix4 mat)
{
	double res[4] = { 0, 0, 0, 0 };

	for (size_t i = 0; i < 4; i++)
	{
		res[i] =
			x * mat.At(i, 0) +
			y * mat.At(i, 1) +
			z * mat.At(i, 2) +
			w * mat.At(i, 3);
	}

	return 
		Vector4D(
			res[0],
			res[1],
			res[2],
			res[3]
		);
}

Vector4D Vector4D::operator/(const double scalar)
{
	return
		Vector4D(
			x / scalar,
			y / scalar,
			z / scalar,
			w / scalar
		);
}
