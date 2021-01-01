#include "DirectionalLight.h"

#include "Vector3D.h"
#include "Color.h"

using namespace softengine;

DirectionalLight::DirectionalLight(
	Vector3D direction)
  :
	Light(
		true,
		Vector3D(0.0, 0.0, 0.0),
		direction,
		Color::White,
		Attenuation()
	)
{

}

DirectionalLight::DirectionalLight(
	Vector3D direction,
	Color color)
  :
	Light(
		true,
		Vector3D(0.0, 0.0, 0.0),
		direction,
		color,
		Attenuation()
	)
{

}

DirectionalLight::DirectionalLight(
	Vector3D direction,
	Attenuation attenuation)
  :
	Light(
		true,
		Vector3D(0.0, 0.0, 0.0),
		direction,
		Color::White,
		Attenuation()
	)
{

}

DirectionalLight::DirectionalLight(
	Vector3D direction,
	Color color,
	Attenuation attenuation)
  :
	Light(
		true,
		Vector3D(0.0, 0.0, 0.0),
		direction,
		color,
		attenuation
	)
{

}
