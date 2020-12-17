#include "Matrix4.h"
#include "Matrix3.h"
#include "Frame3D.h"
#include <iostream>

using namespace softengine;

Matrix4::Matrix4(const Matrix4& matrix)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}
}

Matrix4::Matrix4(
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

double Matrix4::At(
	size_t row, 
	size_t col) const
{
	if (row < 0 ||
		row > 3 ||
		col < 0 ||
		col > 3)
	{
		throw std::runtime_error("Matrix index out of range");
	}

	return m[row][col];
}

void Matrix4::At(
	size_t row, 
	size_t col, 
	double val)
{
	if (row < 0 ||
		row > 3 ||
		col < 0 ||
		col > 3)
	{
		throw std::runtime_error("Matrix index out of range");
	}

	m[row][col] = val;
}

double Matrix4::Determinant()
{
	Matrix3 a(
		m[1][1], m[1][2], m[1][3],
		m[2][1], m[2][2], m[2][3],
		m[3][1], m[3][2], m[3][3]
	);
	Matrix3 b(
		m[1][0], m[1][2], m[1][3],
		m[2][0], m[2][2], m[2][3],
		m[3][0], m[3][2], m[3][3]
	);
	Matrix3 c(
		m[1][0], m[1][1], m[1][3],
		m[2][0], m[2][1], m[2][3],
		m[3][0], m[3][1], m[3][3]
	);
	Matrix3 d(
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2],
		m[3][0], m[3][1], m[3][2]
	);

	return
		m[0][0] * a.Determinant() -
		m[0][1] * b.Determinant() +
		m[0][2] * c.Determinant() -
		m[0][3] * d.Determinant();
}

Matrix4 Matrix4::Transposed()
{
	double res[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	res[0][0] = m[0][0];
	res[0][1] = m[1][0];
	res[0][2] = m[2][0];
	res[0][3] = m[3][0];

	res[1][0] = m[0][1];
	res[1][1] = m[1][1];
	res[1][2] = m[2][1];
	res[1][3] = m[3][1];

	res[2][0] = m[0][2];
	res[2][1] = m[1][2];
	res[2][2] = m[2][2];
	res[2][3] = m[3][2];

	res[3][0] = m[0][3];
	res[3][1] = m[1][3];
	res[3][2] = m[2][3];
	res[3][3] = m[3][3];

	return Matrix4(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	);
}

Matrix4 Matrix4::Adjugate()
{
	double res[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	Matrix3 a(
		m[1][1], m[1][2], m[1][3],
		m[2][1], m[2][2], m[2][3],
		m[3][1], m[3][2], m[3][3]
	);
	Matrix3 b(
		m[1][0], m[1][2], m[1][3],
		m[2][0], m[2][2], m[2][3],
		m[3][0], m[3][2], m[3][3]
	);
	Matrix3 c(
		m[1][0], m[1][1], m[1][3],
		m[2][0], m[2][1], m[2][3],
		m[3][0], m[3][1], m[3][3]
	);
	Matrix3 d(
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2],
		m[3][0], m[3][1], m[3][2]
	);

	Matrix3 e(
		m[0][1], m[0][2], m[0][3],
		m[2][1], m[2][2], m[2][3],
		m[3][1], m[3][2], m[3][3]
	);
	Matrix3 f(
		m[0][0], m[0][2], m[0][3],
		m[2][0], m[2][2], m[2][3],
		m[3][0], m[3][2], m[3][3]
	);
	Matrix3 g(
		m[0][0], m[0][1], m[0][3],
		m[2][0], m[2][1], m[2][3],
		m[3][0], m[3][1], m[3][3]
	);
	Matrix3 h(
		m[0][0], m[0][1], m[0][2],
		m[2][0], m[2][1], m[2][2],
		m[3][0], m[3][1], m[3][2]
	);

	Matrix3 i(
		m[0][1], m[0][2], m[0][3],
		m[1][1], m[1][2], m[1][3],
		m[3][1], m[3][2], m[3][3]
	);
	Matrix3 j(
		m[0][0], m[0][2], m[0][3],
		m[1][0], m[1][2], m[1][3],
		m[3][0], m[3][2], m[3][3]
	);
	Matrix3 k(
		m[0][0], m[0][1], m[0][3],
		m[1][0], m[1][1], m[1][3],
		m[3][0], m[3][1], m[3][3]
	);
	Matrix3 l(
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[3][0], m[3][1], m[3][2]
	);

	Matrix3 mm(
		m[0][1], m[0][2], m[0][3],
		m[1][1], m[1][2], m[1][3],
		m[2][1], m[2][2], m[2][3]
	);
	Matrix3 n(
		m[0][0], m[0][2], m[0][3],
		m[1][0], m[1][2], m[1][3],
		m[2][0], m[2][2], m[2][3]
	);
	Matrix3 o(
		m[0][0], m[0][1], m[0][3],
		m[1][0], m[1][1], m[1][3],
		m[2][0], m[2][1], m[2][3]
	);
	Matrix3 p(
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2]
	);

	res[0][0] = a.Determinant();
	res[0][1] = -b.Determinant();
	res[0][1] = c.Determinant();
	res[0][2] = -d.Determinant();

	res[1][0] = e.Determinant();
	res[1][1] = -f.Determinant();
	res[1][2] = g.Determinant();
	res[1][3] = -h.Determinant();

	res[2][0] = i.Determinant();
	res[2][1] = -j.Determinant();
	res[2][2] = k.Determinant();
	res[2][3] = -l.Determinant();

	res[3][0] = mm.Determinant();
	res[3][1] = -n.Determinant();
	res[3][2] = o.Determinant();
	res[3][3] = -p.Determinant();

	return Matrix4(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	).Transposed();
}

Matrix4 Matrix4::Inverse()
{
	return Matrix4(*this).Adjugate() * (1 / Determinant());
}

Matrix4 Matrix4::operator*(const double& rhs)
{
	double res[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res[i][j] = m[i][j] * rhs;
		}
	}

	return Matrix4(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	);
}

Matrix4 Matrix4::operator*(const Matrix4& rhs)
{
	double res[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				res[i][j] += m[i][k] * rhs.At(k, j);
			}
		}
	}

	return Matrix4(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	);
}

Matrix4 Matrix4::operator*(const Frame3D& rhs)
{
	double res[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				res[i][j] += m[i][k] * rhs.Matrix().At(k, j);
			}
		}
	}

	return Matrix4(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	);
}

Matrix4 Matrix4::Zeros()
{
	return 
		Matrix4(
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0
		);
}

Matrix4 Matrix4::Identity()
{
	return
		Matrix4(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
}
