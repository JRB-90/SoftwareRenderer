#include "SceneLighting.h"

using namespace softengine;

SceneLighting::SceneLighting()
  :
	ambientLight(
		AmbientLight(
			Color::White,
			1.0
		)
	)
{
}

AmbientLight& SceneLighting::GetAmbientLight()
{
	return ambientLight;
}

void SceneLighting::SetAmbientLight(AmbientLight ambientLight)
{
	this->ambientLight = ambientLight;
}

std::vector<DirectionalLight>& SceneLighting::GetDirectionalLights()
{
	return directionalLights;
}

void SceneLighting::ClearAll()
{
	ambientLight =
		AmbientLight(
			Color::White,
			1.0
		);
	directionalLights.clear();
}
