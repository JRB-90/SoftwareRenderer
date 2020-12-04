#include "Frame2D.h"
#include "MathUtils.h"
#include <cmath>

using namespace softengine;

Frame2D::Frame2D()
  :
	angle(0.0),
	scale(Vector2D(1.0, 1.0))
{
	CalculateMatrix();
}

Frame2D::Frame2D(Vector2D position)
  :
	position(position),
	angle(0.0),
	scale(Vector2D(1.0, 1.0))
{
	CalculateMatrix();
}

Frame2D::Frame2D(double angle)
  :
	angle(angle),
	scale(Vector2D(1.0, 1.0))
{
	CalculateMatrix();
}

Frame2D::Frame2D(
	Vector2D position, 
	double angle)
  :
	position(position),
	angle(angle),
	scale(Vector2D(1.0, 1.0))
{
	CalculateMatrix();
}

Frame2D::Frame2D(
	Vector2D position, 
	Vector2D scale)
  :
	position(position),
	angle(0.0),
	scale(scale)
{
	CalculateMatrix();
}

Frame2D::Frame2D(
	Vector2D position, 
	double angle, 
	Vector2D scale)
  :
	position(position),
	angle(angle),
	scale(scale)
{
	CalculateMatrix();
}

Frame2D::Frame2D(
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

	position = Vector2D(
		m[0][2],
		m[1][2]
	);
	angle = MathUtils::ToDeg(std::atan2(m[1][0], m[0][0]));

	double sx = std::sqrt((m[0][0] * m[0][0]) + (m[0][1] * m[0][1]));
	if (m[0][0] < 0)
	{
		sx *= -1.0;
	}
	double sy = std::sqrt((m[1][0] * m[1][0]) + (m[1][1] * m[1][1]));
	if (m[1][1] < 0)
	{
		sy *= -1.0;
	}
	scale = Vector2D(sx, sy);
}

void Frame2D::CalculateMatrix()
{
	double angleRad = MathUtils::ToRad(angle);

	Frame2D s(
		scale.X(),				0,						0,
		0,						scale.Y(),				0,
		0,						0,						1.0
	);

	Frame2D r(
		std::cos(angleRad), -std::sin(angleRad), 0.0,
		std::sin(angleRad), std::cos(angleRad), 0.0,
		0, 0, 1.0
	);

	Frame2D t(
		1.0,					0.0,					position.X(),
		0.0,					1.0,					position.Y(),
		0.0,					0.0,					1.0
	);

	Frame2D res = (s * r) * t;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			m[i][j] = res.At(i, j);
		}
	}
}

double Frame2D::At(
	size_t row, 
	size_t col) const
{
	return m[row][col];
}

Frame2D Frame2D::Inverse()
{
	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	res[0][0] = m[1][1];
	res[0][1] = m[1][0];
	res[0][2] = m[0][2];
	res[1][0] = m[0][1];
	res[1][1] = m[0][0];
	res[1][2] = m[1][2];
	res[0][2] = -m[0][2];
	res[1][2] = -m[1][2];
	res[2][2] = m[2][2];

	return Frame2D(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Frame2D Frame2D::RelativeTransform(
	Frame2D& from,
	Frame2D& to)
{
	return from.Inverse() * to;
}

Frame2D Frame2D::operator*(const Frame2D& rhs)
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

	return Frame2D(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}
