#pragma once

#include "Color.h"
#include "Texture.h"
#include "ShadingType.h"

namespace softengine
{
	class Material
	{
	public:
		Material();
		Material(const Material& material);
		Material(Color& baseColor);
		Material(
			Color& baseColor,
			double shininess
		);
		Material(
			Color& baseColor,
			ShadingType shadingType
		);
		Material(
			Color& baseColor,
			double shininess,
			ShadingType shadingType
		);
		Material(Texture& texture);
		Material(
			Texture& texture,
			double shininess
		);
		Material(
			Texture& texture,
			ShadingType shadingType
		);
		Material(
			Texture& texture,
			double shininess,
			ShadingType shadingType
		);
		Material(
			Color& ambient,
			Color& diffuse,
			Color& specular
		);
		Material(
			Color& ambient,
			Color& diffuse,
			Color& specular,
			double shininess
		);
		Material(
			Color& ambient,
			Color& diffuse,
			Color& specular,
			ShadingType shadingType
		);
		Material(
			Color& ambient,
			Color& diffuse,
			Color& specular,
			double shininess,
			ShadingType shadingType
		);

		Color& Ambient() { return ambient; }
		void Ambient(Color& ambient) { this->ambient = ambient; }
		Color& Difffuse() { return diffuse; }
		void Difffuse(Color& diffuse) { this->diffuse = diffuse; }
		Color& Specular() { return specular; }
		void Specular(Color& specular) { this->specular = specular; }
		double Shininess() { return shininess; }
		void Shininess(double shininess) { this->shininess = shininess; }
		ShadingType GetShadingType() { return shadingType; }
		void SetShadingType(ShadingType shadingType) { this->shadingType = shadingType; }
		Texture& GetTexture() { return texture; }
		void SetTexture(Texture& texture) { this->texture = texture; }

	private:
		Color ambient;
		Color diffuse;
		Color specular;
		double shininess;
		ShadingType shadingType;
		Texture texture;

		void CalculateDefaultMaterialProperties(Color& color);
	};
}