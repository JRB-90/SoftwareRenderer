#pragma once

namespace softengine
{
	class Frame3D;

	class Matrix4
	{
	public:
		Matrix4(const Matrix4& matrix);
		Matrix4();
		Matrix4(
			double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23,
			double m30, double m31, double m32, double m33
		);

		double At(
			size_t row, 
			size_t col
		) const;
		void At(
			size_t row, 
			size_t col, 
			double val
		);
		double Determinant();
		Matrix4 Transposed();
		Matrix4 Adjugate();
		Matrix4 Inverse();

		Matrix4 operator*(const double& rhs);
		Matrix4 operator*(const Matrix4& rhs);
		Matrix4 operator*(const Frame3D& rhs);

		static Matrix4 Zeros();
		static Matrix4 Identity();

	private:
		double m[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	};
}