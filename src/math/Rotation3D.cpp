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

	m[0][0] = 1 - 2 * (yy + zz);
	m[0][1] = 2 * (xy - zw);
	m[0][2] = 2 * (xz + yw);
	m[1][0] = 2 * (xy + zw);
	m[1][1] = 1 - 2 * (xx + zz);
	m[1][2] = 2 * (yz - xw);
	m[2][0] = 2 * (xz - yw);
	m[2][1] = 2 * (yz + xw);
	m[2][2] = 1 - 2 * (xx + yy);
}

Rotation3D::Rotation3D(
	double m00, double m01, double m02, 
	double m10, double m11, double m12, 
	double m20, double m21, double m22)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;

	CalculateFromMatrix();
}

double Rotation3D::At(
	size_t row, 
	size_t col) const
{
	return m[row][col];
}

Quaternion Rotation3D::AsQuaternion()
{
	return Quaternion(*this);
}

Rotation3D Rotation3D::Inverse()
{
	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	res[0][0] = m[0][0];
	res[0][1] = m[1][0];
	res[0][2] = m[2][0];
	res[1][0] = m[0][1];
	res[1][1] = m[1][1];
	res[1][2] = m[2][1];
	res[2][0] = m[0][2];
	res[2][1] = m[1][2];
	res[2][2] = m[2][2];

	return Rotation3D(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Rotation3D Rotation3D::operator*(const Rotation3D& rhs)
{
	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				res[i][j] += m[i][k] * rhs.At(k, j);
			}
		}
	}

	return Rotation3D(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

void Rotation3D::CalculateMatrix()
{
	double sx = std::sin(MathUtils::ToRad(rx));
	double sy = std::sin(MathUtils::ToRad(ry));
	double sz = std::sin(MathUtils::ToRad(rz));
	double cx = std::cos(MathUtils::ToRad(rx));
	double cy = std::cos(MathUtils::ToRad(ry));
	double cz = std::cos(MathUtils::ToRad(rz));

	m[0][0] = cy * cz;
	m[0][1] = cz * sx * sy - cx * sz;
	m[0][2] = cx * cz * sy + sx * sz;
	m[1][0] = cy * sz;
	m[1][1] = cx * cz + sx * sy * sz;
	m[1][2] = -cz * sx + cx * sy * sz;
	m[2][0] = -sy;
	m[2][1] = cy * sx;
	m[2][2] = cx * cy;
}

void Rotation3D::CalculateFromMatrix()
{
	if (m[2][0] < 1)
	{
		if (m[2][0] > -1)
		{
			ry = MathUtils::ToDeg(std::asin(-m[2][0]));
			rz = MathUtils::ToDeg(std::atan2(m[1][0] / std::cos(ry), m[0][0] / std::cos(ry)));
			rx = MathUtils::ToDeg(std::atan2(m[2][1] / std::cos(ry), m[2][2] / std::cos(ry)));
		}
		else
		{
			ry = MathUtils::ToDeg(M_PI / 2);
			rz = 0.0;
			rx = MathUtils::ToDeg(std::atan2(m[0][1], m[0][2]));
		}
	}
	else
	{
		ry = MathUtils::ToDeg(-M_PI / 2);
		rz = 0.0;
		rx = MathUtils::ToDeg(std::atan2(-m[0][1], -m[0][2]));
	}
}
