#include "Light.h"

#include "Vector3D.h"
#include "Color.h"

using namespace softengine;

Light::Light(
	bool isEnabled,
	Vector3D position,
	Vector3D direction,
	Color color,
	Attenuation attenuation)
  :
	isEnabled(isEnabled),
	position(position),
	direction(direction),
	color(color),
	attenuation(attenuation)
{
}
