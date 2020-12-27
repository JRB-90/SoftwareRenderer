#pragma once

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include <vector>

namespace softengine
{
	class SceneLighting
	{
	public:
		SceneLighting();

		AmbientLight& GetAmbientLight();
		void SetAmbientLight(AmbientLight ambientLight);
		std::vector<DirectionalLight>& GetDirectionalLights();

		void ClearAll();

	private:
		AmbientLight ambientLight;
		std::vector<DirectionalLight> directionalLights;
	};
}