#include "AmbientLight.h"

#include "Vector3D.h"
#include "Color.h"

using namespace softengine;

AmbientLight::AmbientLight(
	Color color,
	double strength)
  :
	Light(
		true,
		Vector3D(0.0, 0.0, 0.0),
		Vector3D(0.0, 0.0, 0.0),
		color,
		Attenuation()
	),
	strength(strength)
{
}