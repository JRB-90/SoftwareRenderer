#pragma once

namespace softengine
{
	class Frame2D;

	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(
			const Vector2D& vector
		);
		Vector2D(
			double x,
			double y
		);

		double X() const { return x; }
		void X(double x) { this->x = x; }
		double Y() const { return y; }
		void Y(double y) { this->y = y; }
		double Length();
		void Normalise();
		Vector2D Normalised();

		Vector2D operator+(const Vector2D& vec);
		Vector2D operator-(const Vector2D& vec);
		Vector2D operator*(const double scalar);
		Vector2D operator*(const Frame2D& frame);
		Vector2D operator/(const double scalar);

	private:
		double x;
		double y;
	};
}