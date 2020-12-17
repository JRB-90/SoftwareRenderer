#pragma once

#include "Vector3D.h"
#include "Rotation3D.h"
#include "Matrix4.h"

namespace softengine
{
	class Frame3D
	{
	public:
		Frame3D();
		Frame3D(Matrix4 matrix);
		Frame3D(
			Vector3D translation
		);
		Frame3D(
			Rotation3D rotation
		);
		Frame3D(
			Vector3D translation,
			Rotation3D rotation
		);
		Frame3D(
			double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23,
			double m30, double m31, double m32, double m33
		);

		Vector3D& Translation() { return translation; }
		void Tranlation(Vector3D& translation) { this->translation = translation; CalculateMatrix(); }
		Rotation3D& Rotation() { return rotation; }
		void Rotation(Rotation3D& rotation) { this->rotation = rotation; CalculateMatrix(); }
		Matrix4 Matrix() const { return m; }

		Frame3D Inverse();

		static Frame3D RelativeTransform(
			Frame3D& from,
			Frame3D& to
		);

		Frame3D operator*(const Frame3D& rhs);
		Frame3D operator*(const Matrix4& rhs);

	private:
		Vector3D translation;
		Rotation3D rotation;
		Matrix4 m = Matrix4::Identity();

		void CalculateMatrix();
		void CalculateFromMatrix();
	};
}