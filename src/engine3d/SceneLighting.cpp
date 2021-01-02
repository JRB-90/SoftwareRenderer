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

void SceneLighting::ClearAll()
{
	ambientLight =
		AmbientLight(
			Color::White,
			1.0
		);
	directionalLights.clear();
	pointLights.clear();
}
