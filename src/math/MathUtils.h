#pragma once

#include <cinttypes>

namespace softengine
{
	class Vector2D;
	class Frame2D;
	class Matrix4;

	class MathUtils
	{
	public:
		MathUtils() = delete;

		static double ToRad(double deg);
		static double ToDeg(double rad);
		static Vector2D TransformPointFor2D(
			Vector2D& position,
			Frame2D& transform
		);
		static int Interpolate(
			int val1,
			int val2,
			double factor
		);
		static double Interpolate(
			double val1,
			double val2,
			double factor
		);
		static void PrintMatrix4(Matrix4 mat);
	};
}