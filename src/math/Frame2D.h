#pragma once

#include "Vector2D.h"

namespace softengine
{
	class Frame2D
	{
	public:
		Frame2D();
		Frame2D(
			Vector2D translation
		);
		Frame2D(
			double angle
		);
		Frame2D(
			Vector2D translation,
			double angle
		);
		Frame2D(
			Vector2D translation,
			Vector2D scale
		);
		Frame2D(
			Vector2D translation,
			double angle,
			Vector2D scale
		);
		Frame2D(
			Vector2D translation,
			double angle,
			double scale
		);
		Frame2D(
			double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22
		);

		Vector2D& Translation() { return translation; }
		void Translation(Vector2D& translation) { this->translation = translation; CalculateMatrix(); }
		double Angle() { return angle; }
		void Angle(double angle) { this->angle = angle; CalculateMatrix(); }
		Vector2D& Scale() { return scale; }
		void Scale(Vector2D& scale) { this->scale = scale; CalculateMatrix(); }
		void Scale(double scale) { this->scale = Vector2D(scale, scale); CalculateMatrix(); }

		double At(size_t row, size_t col) const;
		Frame2D Inverse();
		
		static Frame2D RelativeTransform(
			Frame2D& from,
			Frame2D& to
		);

		Frame2D operator*(const Frame2D& rhs);

	private:
		Vector2D translation;
		double angle;
		Vector2D scale;
		double m[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		void CalculateMatrix();
	};
}