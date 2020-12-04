#pragma once

#include "Vector2D.h"
#include "Frame2D.h"

namespace softengine
{
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
	};
}