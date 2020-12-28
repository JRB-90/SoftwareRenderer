#define _USE_MATH_DEFINES

#include "Rotation3D.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "MathUtils.h"
#include <cmath>

using namespace softengine;

Rotation3D::Rotation3D()
  :
	rx(0.0),
	ry(0.0),
	rz(0.0)
{
	CalculateMatrix();
}

Rotation3D::Rotation3D(
	double rx, 
	double ry, 
	double rz)
  :
	rx(rx),
	ry(ry),
	rz(rz)
{
	CalculateMatrix();
}

Rotation3D::Rotation3D(Vector3D vector)
  :
	rx(vector.X()),
	ry(vector.Y()),
	rz(vector.Z())
{
	CalculateMatrix();
}

Rotation3D::Rotation3D(Quaternion quaternion)
{
	auto q = quaternion.Normalised();

	double xx = q.X() * q.X();
	double xy = q.X() * q.Y();
	double xz = q.X() * q.Z();
	double xw = q.X() * q.W();
	double yy = q.Y() * q.Y();
	double yz = q.Y() * q.Z();
	double yw = q.Y() * q.W();
	double zz = q.Z() * q.Z();
	double zw = q.Z() * q.W();

	m.At(0, 0, 1 - 2 * (yy + zz));
	m.At(0, 1, 2 * (xy - zw));
	m.At(0, 2, 2 * (xz + yw));
	m.At(1, 0, 2 * (xy + zw));
	m.At(1, 1, 1 - 2 * (xx + zz));
	m.At(1, 2, 2 * (yz - xw));
	m.At(2, 0, 2 * (xz - yw));
	m.At(2, 1, 2 * (yz + xw));
	m.At(2, 2, 1 - 2 * (xx + yy));
}

Rotation3D::Rotation3D(Matrix3 mat)
  :
	m(mat)
{
	CalculateFromMatrix();
}

Rotation3D::Rotation3D(
	Vector3D xAxis, 
	Vector3D yAxis, 
	Vector3D zAxis)
{
	m = Matrix3(
		xAxis.X(), yAxis.X(), zAxis.X(),
		xAxis.Y(), yAxis.Y(), zAxis.Y(),
		xAxis.Z(), yAxis.Z(), zAxis.Z()
	);

	CalculateFromMatrix();
}

Rotation3D::Rotation3D(
	double m00, double m01, double m02, 
	double m10, double m11, double m12, 
	double m20, double m21, double m22)
{
	m = Matrix3(
		m00, m01, m02,
		m10, m11, m12,
		m20, m21, m22
	);

	CalculateFromMatrix();
}

Quaternion Rotation3D::AsQuaternion()
{
	return Quaternion(*this);
}

Rotation3D Rotation3D::Inverse()
{
	// TODO - Does this need to be MAtrix3.Inverse?

	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	res[0][0] = m.At(0, 0);
	res[0][1] = m.At(1, 0);
	res[0][2] = m.At(2, 0);
	res[1][0] = m.At(0, 1);
	res[1][1] = m.At(1, 1);
	res[1][2] = m.At(2, 1);
	res[2][0] = m.At(0, 2);
	res[2][1] = m.At(1, 2);
	res[2][2] = m.At(2, 2);

	return Rotation3D(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Rotation3D Rotation3D::operator*(const Rotation3D& rhs)
{
	return Rotation3D(m * rhs.m);
}

void Rotation3D::CalculateMatrix()
{
	double sx = std::sin(MathUtils::ToRad(rx));
	double sy = std::sin(MathUtils::ToRad(ry));
	double sz = std::sin(MathUtils::ToRad(rz));
	double cx = std::cos(MathUtils::ToRad(rx));
	double cy = std::cos(MathUtils::ToRad(ry));
	double cz = std::cos(MathUtils::ToRad(rz));

	m.At(0, 0, cy * cz);
	m.At(0, 1, cz * sx * sy - cx * sz);
	m.At(0, 2, cx * cz * sy + sx * sz);
	m.At(1, 0, cy * sz);
	m.At(1, 1, cx * cz + sx * sy * sz);
	m.At(1, 2, -cz * sx + cx * sy * sz);
	m.At(2, 0, -sy);
	m.At(2, 1, cy * sx);
	m.At(2, 2, cx * cy);
}

void Rotation3D::CalculateFromMatrix()
{
	if (m.At(2, 0) < 1)
	{
		if (m.At(2, 0)> -1)
		{
			ry = MathUtils::ToDeg(std::asin(-m.At(2, 0)));
			rz = MathUtils::ToDeg(std::atan2(m.At(1, 0) / std::cos(ry), m.At(0, 0) / std::cos(ry)));
			rx = MathUtils::ToDeg(std::atan2(m.At(2, 1) / std::cos(ry), m.At(2, 2) / std::cos(ry)));
		}
		else
		{
			ry = MathUtils::ToDeg(M_PI / 2);
			rz = 0.0;
			rx = MathUtils::ToDeg(std::atan2(m.At(0, 1), m.At(0, 2)));
		}
	}
	else
	{
		ry = MathUtils::ToDeg(-M_PI / 2);
		rz = 0.0;
		rx = MathUtils::ToDeg(std::atan2(-m.At(0, 1), -m.At(0, 2)));
	}
}
