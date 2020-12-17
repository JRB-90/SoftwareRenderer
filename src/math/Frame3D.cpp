#include "Frame3D.h"

using namespace softengine;

Frame3D::Frame3D()
{
	CalculateMatrix();
}

Frame3D::Frame3D(Vector3D translation)
  :
	translation(translation)
{
	CalculateMatrix();
}

Frame3D::Frame3D(Rotation3D rotation)
  :
	rotation(rotation)
{
	CalculateMatrix();
}

Frame3D::Frame3D(
	Vector3D translation,
	Rotation3D rotation)
  :
	translation(translation),
	rotation(rotation)
{
	CalculateMatrix();
}

Frame3D::Frame3D(
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

	translation = Vector3D(
		m[0][3],
		m[1][3],
		m[2][3]
	);

	rotation = Rotation3D(
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2]
	);
}

double Frame3D::At(
	size_t row, 
	size_t col) const
{
	return m[row][col];
}

Frame3D Frame3D::Inverse()
{
	Rotation3D rotInv = rotation.Inverse();
	Vector3D transInv = (translation * -1.0) * rotInv;

	return 
		Frame3D(
			transInv,
			rotInv
		);
}

Frame3D Frame3D::RelativeTransform(
	Frame3D& from, 
	Frame3D& to)
{
	return from.Inverse() * to;
}

Frame3D Frame3D::operator*(const Frame3D& rhs)
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

	return Frame3D(
		res[0][0], res[0][1], res[0][2], res[0][3],
		res[1][0], res[1][1], res[1][2], res[1][3],
		res[2][0], res[2][1], res[2][2], res[2][3],
		res[3][0], res[3][1], res[3][2], res[3][3]
	);
}

void Frame3D::CalculateMatrix()
{
	m[0][0] = rotation.At(0, 0);
	m[0][1] = rotation.At(0, 1);
	m[0][2] = rotation.At(0, 2);
	m[1][0] = rotation.At(1, 0);
	m[1][1] = rotation.At(1, 1);
	m[1][2] = rotation.At(1, 2);
	m[2][0] = rotation.At(2, 0);
	m[2][1] = rotation.At(2, 1);
	m[2][2] = rotation.At(2, 2);

	m[0][3] = translation.X();
	m[1][3] = translation.Y();
	m[2][3] = translation.Z();

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
}
