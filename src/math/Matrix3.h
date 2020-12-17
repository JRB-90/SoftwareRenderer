#pragma once

namespace softengine
{
	class Rotation3D;

	class Matrix3
	{
	public:
		Matrix3(const Matrix3& matrix);
		Matrix3(
			double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22
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
		Matrix3 Transposed();
		Matrix3 Adjugate();;
		Matrix3 Inverse();

		Matrix3 operator*(const double& rhs);
		Matrix3 operator*(const Matrix3& rhs);
		Matrix3 operator*(const Rotation3D& rhs);

		static Matrix3 Zeros();
		static Matrix3 Identity();

	private:
		double m[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	};
}