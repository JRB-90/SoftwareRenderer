#pragma once

#include "Color.h"
#include "Vector3D.h"

namespace softengine
{
	enum class LightType
	{
		Ambient,
		Directional,
		Point
	};

	struct Attenuation
	{
		double Constant;
		double Linear;
		double Quadratic;

		Attenuation()
		{
			Constant = 0.0;
			Linear = 1.0;
			Quadratic = 0.0;
		}

		Attenuation(
			double constant,
			double linear,
			double quadratic)
		{
			Constant = constant;
			Linear = linear;
			Quadratic = quadratic;
		}
	};

	class Light
	{
	public:
		Light() = delete;

		bool IsEnabled() { return isEnabled; }
		void IsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }
		Vector3D& Position() { return position; }
		void Position(Vector3D& position) { this->position = position; }
		Vector3D& Direction() { return direction; }
		void Direction(Vector3D& direction) { this->direction = direction; }
		Color GetColor() { return color; }
		void SetColor(Color color) { this->color = color; }
		Attenuation& GetAttenuation() { return attenuation; }
		void SetAttenuation(Attenuation& attenuation) { this->attenuation = attenuation; }
		virtual LightType GetLightType() const = 0;

	protected:
		Light(
			bool isEnabled,
			Vector3D position,
			Vector3D direction,
			Color color,
			Attenuation attenuation
		);

		bool isEnabled;
		Vector3D position;
		Vector3D direction;
		Color color;
		Attenuation attenuation;
		double spotCutoff;
		double spotExponent;
	};
}