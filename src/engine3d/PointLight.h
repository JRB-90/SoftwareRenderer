#pragma once

#include "Light.h"

namespace softengine
{
	class Color;
	class Vector3D;
	
	class PointLight : public Light
	{
	public:
		PointLight();
		PointLight(Vector3D position);
		PointLight(Color color);
		PointLight(Attenuation attenuation);
		PointLight(
			Color color,
			Attenuation attenuation
		);
		PointLight(
			Vector3D position,
			Color color
		);
		PointLight(
			Vector3D position,
			Attenuation attenuation
		);
		PointLight(
			Vector3D position,
			Color color,
			Attenuation attenuation
		);

		virtual LightType GetLightType() const { return LightType::Point; }
	};
}