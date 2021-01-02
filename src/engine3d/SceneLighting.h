#pragma once

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <vector>

namespace softengine
{
	class SceneLighting
	{
	public:
		SceneLighting();

		AmbientLight& GetAmbientLight() { return ambientLight; }
		void SetAmbientLight(AmbientLight ambientLight) {this->ambientLight = ambientLight; }
		std::vector<DirectionalLight>& GetDirectionalLights() { return directionalLights; }
		std::vector<PointLight>& GetPointsLights() { return pointLights; }

		void ClearAll();

	private:
		AmbientLight ambientLight;
		std::vector<DirectionalLight> directionalLights;
		std::vector<PointLight> pointLights;
	};
}