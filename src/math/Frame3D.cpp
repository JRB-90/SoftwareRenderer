#include "Frame3D.h"
#include "Matrix4.h"

using namespace softengine;

Frame3D::Frame3D()
{
	CalculateMatrix();
}

Frame3D::Frame3D(Matrix4 matrix)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m.At(i, j, matrix.At(i, j));
		}
	}

	CalculateFromMatrix();
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
	m.At(0, 0, m00);
	m.At(0, 1, m01);
	m.At(0, 2, m02);
	m.At(0, 3, m03);
	m.At(1, 0, m10);
	m.At(1, 1, m11);
	m.At(1, 2, m12);
	m.At(1, 3, m13);
	m.At(2, 0, m20);
	m.At(2, 1, m21);
	m.At(2, 2, m22);
	m.At(2, 3, m23);
	m.At(3, 0, m30);
	m.At(3, 1, m31);
	m.At(3, 2, m32);
	m.At(3, 3, m33);

	CalculateFromMatrix();
}

Frame3D Frame3D::Inverse()
{
	// TODO - Does Matrix4.Inverse want to go here?

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
	return Frame3D(m * rhs.m);
}

Frame3D Frame3D::operator*(const Matrix4& rhs)
{
	return Frame3D(m * rhs);
}

void Frame3D::CalculateMatrix()
{
	m.At(0, 0, rotation.Matrix().At(0, 0));
	m.At(0, 1, rotation.Matrix().At(0, 1));
	m.At(0, 2, rotation.Matrix().At(0, 2));
	m.At(1, 0, rotation.Matrix().At(1, 0));
	m.At(1, 1, rotation.Matrix().At(1, 1));
	m.At(1, 2, rotation.Matrix().At(1, 2));
	m.At(2, 0, rotation.Matrix().At(2, 0));
	m.At(2, 1, rotation.Matrix().At(2, 1));
	m.At(2, 2, rotation.Matrix().At(2, 2));

	m.At(0, 3, translation.X());
	m.At(1, 3, translation.Y());
	m.At(2, 3, translation.Z());

	m.At(3, 0, 0.0);
	m.At(3, 1, 0.0);
	m.At(3, 2, 0.0);
	m.At(3, 3, 1.0);
}

void Frame3D::CalculateFromMatrix()
{
	translation = Vector3D(
		m.At(0, 3),
		m.At(1, 3),
		m.At(2, 3)
	);

	rotation = Rotation3D(
		m.At(0, 0), m.At(0, 1), m.At(0, 2),
		m.At(1, 0), m.At(1, 1), m.At(1, 2),
		m.At(2, 0), m.At(2, 1), m.At(2, 2)
	);
}
