#pragma once

namespace softengine
{
	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(
			const Vector3D& vector
		);
		Vector3D(
			double x,
			double y,
			double z
		);

		double X() const { return x; }
		void X(double x) { this->x = x; }
		double Y() const { return y; }
		void Y(double y) { this->y = y; }
		double Z() const { return z; }
		void Z(double z) { this->z = z; }
		double Length();
		void Normalise();
		Vector3D Normalised();

		Vector3D operator+(const Vector3D& vec);
		Vector3D operator-(const Vector3D& vec);
		Vector3D operator*(const double scalar);
		Vector3D operator/(const double scalar);

	private:
		double x;
		double y;
		double z;
	};
}