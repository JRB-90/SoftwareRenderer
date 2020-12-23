#pragma once

#include "Light.h"

namespace softengine
{
	class Color;

	class AmbientLight : public Light
	{
	public:
		AmbientLight(
			Color color,
			double strength
		);

		double Strength() { return strength; }

		virtual LightType GetLightType() const { return LightType::Ambient; }

	private:
		double strength;
	};
}