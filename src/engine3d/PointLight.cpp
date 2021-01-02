#include "PointLight.h"

#include "Color.h"
#include "Vector3D.h"

using namespace softengine;

PointLight::PointLight()
  :
	Light(
		true,
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0),
		Color::White,
		Attenuation()
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(Vector3D position)
  :
	Light(
		true,
		position,
		Vector3D(0, 0, 0),
		Color::White,
		Attenuation()
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(Color color)
  :
	Light(
		true,
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0),
		color,
		Attenuation()
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(Attenuation attenuation)
  :
	Light(
		true,
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0),
		Color::White,
		attenuation
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(
	Color color, 
	Attenuation attenuation)
  :
	Light(
		true,
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0),
		color,
		attenuation
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(
	Vector3D position, 
	Color color)
  :
	Light(
		true,
		position,
		Vector3D(0, 0, 0),
		color,
		Attenuation()
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(
	Vector3D position, 
	Attenuation attenuation)
  :
	Light(
		true,
		position,
		Vector3D(0, 0, 0),
		Color::White,
		attenuation
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}

PointLight::PointLight(
	Vector3D position, 
	Color color, 
	Attenuation attenuation)
  :
	Light(
		true,
		position,
		Vector3D(0, 0, 0),
		color,
		attenuation
	)
{
	spotCutoff = 360.0;
	spotExponent = 0.0;
}
