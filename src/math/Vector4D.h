#pragma once

namespace softengine
{
	class Matrix4;

	class Vector4D
	{
	public:
		Vector4D();
		Vector4D(
			const Vector4D& vector
		);
		Vector4D(
			double x,
			double y,
			double z,
			double w
		);

		double X() const { return x; }
		void X(double x) { this->x = x; }
		double Y() const { return y; }
		void Y(double y) { this->y = y; }
		double Z() const { return z; }
		void Z(double z) { this->z = z; }
		double W() const { return w; }
		void W(double w) { this->w = w; }
		double Length();
		void Normalise();
		Vector4D Normalised();

		Vector4D operator+(const Vector4D& vec);
		Vector4D operator-(const Vector4D& vec);
		Vector4D operator*(const double scalar);
		Vector4D operator*(const Matrix4 mat);
		Vector4D operator/(const double scalar);

	private:
		double x;
		double y;
		double z;
		double w;
	};
}