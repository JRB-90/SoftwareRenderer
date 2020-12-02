#pragma once

namespace softengine
{
	class MathUtils
	{
	public:
		MathUtils() = delete;

		static double ToRad(double deg);
		static double ToDeg(double rad);
	};
}