#pragma once

#include "Matrix3.h"

namespace softengine
{
	class Vector3D;
	class Quaternion;

	class Rotation3D
	{
	public:
		Rotation3D();
		Rotation3D(
			double rx,
			double ry,
			double rz
		);
		Rotation3D(Vector3D vector);
		Rotation3D(Quaternion quaternion);
		Rotation3D(Matrix3 mat);
		Rotation3D(
			double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22
		);

		double Rx() { return rx; }
		void Rx(double rx) { this->rx = rx; CalculateMatrix(); }
		double Ry() { return ry; }
		void Ry(double ry) { this->ry = ry; CalculateMatrix(); }
		double Rz() { return rz; }
		void Rz(double rz) { this->rz = rz; CalculateMatrix(); }

		Matrix3 Matrix() const { return m; }
		Quaternion AsQuaternion();
		Rotation3D Inverse();

		Rotation3D operator*(const Rotation3D& rhs);

	private:
		Matrix3 m = Matrix3::Identity();
		double rx;
		double ry;
		double rz;

		void CalculateMatrix();
		void CalculateFromMatrix();
	};
}