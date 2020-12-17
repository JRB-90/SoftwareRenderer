#include "Matrix3.h"
#include "Rotation3D.h"
#include <iostream>

using namespace softengine;

Matrix3::Matrix3(const Matrix3& matrix)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}
}

Matrix3::Matrix3(
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
}

double Matrix3::At(
	size_t row, 
	size_t col) const
{
	if (row < 0 ||
		row > 2 ||
		col < 0 ||
		col > 2)
	{
		throw std::runtime_error("Matrix index out of range");
	}

	return m[row][col];
}

void Matrix3::At(
	size_t row, 
	size_t col, 
	double val)
{
	if (row < 0 ||
		row > 2 ||
		col < 0 ||
		col > 2)
	{
		throw std::runtime_error("Matrix index out of range");
	}

	m[row][col] = val;
}

double Matrix3::Determinant()
{
	return
		m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
		m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
		m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix3 Matrix3::Transposed()
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

	return Matrix3(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Matrix3 Matrix3::Adjugate()
{
	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	res[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
	res[0][1] = m[1][0] * m[2][2] - m[1][2] * m[2][0];
	res[0][2] = m[1][0] * m[2][1] - m[1][1] * m[2][0];

	res[1][0] = m[0][1] * m[2][2] - m[0][2] * m[2][1];
	res[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
	res[1][2] = m[0][0] * m[2][1] - m[0][1] * m[2][0];

	res[2][0] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	res[2][1] = m[0][0] * m[1][2] - m[0][2] * m[1][0];
	res[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

	res[0][1] *= -1;
	res[1][0] *= -1;
	res[1][2] *= -1;
	res[2][1] *= -1;

	return Matrix3(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	).Transposed();
}

Matrix3 Matrix3::Inverse()
{
	return Matrix3(*this).Adjugate() * (1 / Determinant());
}

Matrix3 Matrix3::operator*(const double& rhs)
{
	double res[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			res[i][j] = m[i][j] * rhs;
		}
	}

	return Matrix3(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Matrix3 Matrix3::operator*(const Matrix3& rhs)
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

	return Matrix3(
		res[0][0], res[0][1], res[0][2],
		res[1][0], res[1][1], res[1][2],
		res[2][0], res[2][1], res[2][2]
	);
}

Matrix3 Matrix3::operator*(const Rotation3D& rhs)
{
	return Matrix3(*this * rhs.Matrix());
}

Matrix3 Matrix3::Zeros()
{
	return
		Matrix3(
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0
		);
}

Matrix3 Matrix3::Identity()
{
	return
		Matrix3(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
}
