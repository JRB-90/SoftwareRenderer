#pragma once

#include "Vector2D.h"

namespace softengine
{
	class Frame2D
	{
	public:
		Frame2D();
		Frame2D(
			Vector2D position
		);
		Frame2D(
			double angle
		);
		Frame2D(
			Vector2D position,
			double angle
		);
		Frame2D(
			double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22
		);

		Vector2D& Position() { return position; }
		void Position(Vector2D& position) { this->position = position; CalculateMatrix(); }
		double Angle() { return angle; }
		void Angle(double angle) { this->angle = angle; CalculateMatrix(); }

		double At(size_t row, size_t col) const;
		Frame2D Inverse();
		
		static Frame2D RelativeTransform(
			Frame2D& from,
			Frame2D& to
		);

		Frame2D operator*(const Frame2D& rhs);

	private:
		Vector2D position;
		double angle;
		double m[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		void CalculateMatrix();
	};
}