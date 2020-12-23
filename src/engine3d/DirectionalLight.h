#pragma once

#include "Light.h"

namespace softengine
{
	class Color;
	class Vector3D;

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(
			Vector3D direction
		);
		DirectionalLight(
			Vector3D direction,
			Color color
		);
		DirectionalLight(
			Vector3D direction,
			Attenuation attenuation
		);
		DirectionalLight(
			Vector3D direction,
			Color color,
			Attenuation attenuation
		);

		virtual LightType GetLightType() const { return LightType::Directional; }
	};
}