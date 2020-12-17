#pragma once

namespace softengine
{
	class Rotation3D;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(
			double x,
			double y,
			double z,
			double w
		);
		Quaternion(Rotation3D& rotation);
		
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
		Quaternion Normalised();
		Rotation3D AsRotation3D();

		// TODO - Finish up quaternion class (operators, inverse etc)

	private:
		double x;
		double y;
		double z;
		double w;
	};
}