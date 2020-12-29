#include "Material.h"

using namespace softengine;

const Color DEFAULT_MAT_COL = Color(0.5, 0.5, 0.5, 1.0);
const Texture DEFAULT_TEXTURE = Texture();
const ShadingType DEFAULT_SHADING_TYPE = ShadingType::None;
const double DEFAULT_AMBIENT_CONST = 0.5;
const double DEFAULT_SPECULAR_CONST = 1.3;
const double DEFAULT_SHININESS = 32.0;

Material::Material()
  :
	shininess(DEFAULT_SHININESS),
	texture(DEFAULT_TEXTURE),
	shadingType(DEFAULT_SHADING_TYPE)
{
	CalculateDefaultMaterialProperties(Color(DEFAULT_MAT_COL));
}

Material::Material(const Material& material)
  :
	ambient(material.ambient),
	diffuse(material.diffuse),
	specular(material.specular),
	shininess(material.shininess),
	texture(material.texture),
	shadingType(material.shadingType)
{
}

Material::Material(Color& baseColor)
  :
	shininess(DEFAULT_SHININESS),
	texture(DEFAULT_TEXTURE),
	shadingType(DEFAULT_SHADING_TYPE)
{
	CalculateDefaultMaterialProperties(baseColor);
}

Material::Material(
	Color& baseColor,
	double shininess)
  :
	shininess(shininess),
	texture(DEFAULT_TEXTURE),
	shadingType(DEFAULT_SHADING_TYPE)
{
	CalculateDefaultMaterialProperties(baseColor);
}

Material::Material(
	Color& baseColor,
	ShadingType shadingType)
  :
	shininess(DEFAULT_SHININESS),
	texture(DEFAULT_TEXTURE),
	shadingType(shadingType)
{
	CalculateDefaultMaterialProperties(baseColor);
}

Material::Material(
	Color& baseColor,
	double shininess,
	ShadingType shadingType)
  :
	shininess(shininess),
	texture(DEFAULT_TEXTURE),
	shadingType(shadingType)
{
	CalculateDefaultMaterialProperties(baseColor);
}

Material::Material(Texture& texture)
  :
	shininess(DEFAULT_SHININESS),
	texture(texture),
	shadingType(DEFAULT_SHADING_TYPE)
{
	CalculateDefaultMaterialProperties(Color(DEFAULT_MAT_COL));
}

Material::Material(
	Texture& texture,
	double shininess)
  :
	shininess(shininess),
	texture(texture),
	shadingType(DEFAULT_SHADING_TYPE)
{
	CalculateDefaultMaterialProperties(Color(DEFAULT_MAT_COL));
}

Material::Material(
	Texture& texture,
	ShadingType shadingType)
  :
	shininess(DEFAULT_SHININESS),
	texture(texture),
	shadingType(shadingType)
{
	CalculateDefaultMaterialProperties(Color(DEFAULT_MAT_COL));
}

Material::Material(
	Texture& texture,
	double shininess,
	ShadingType shadingType)
  :
	shininess(shininess),
	texture(texture),
	shadingType(shadingType)
{
	CalculateDefaultMaterialProperties(Color(DEFAULT_MAT_COL));
}

Material::Material(
	Color& ambient,
	Color& diffuse,
	Color& specular)
  :
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(DEFAULT_SHININESS),
	texture(DEFAULT_TEXTURE),
	shadingType(DEFAULT_SHADING_TYPE)
{
}

Material::Material::Material(
	Color& ambient,
	Color& diffuse,
	Color& specular,
	double shininess)
  :
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess),
	texture(DEFAULT_TEXTURE),
	shadingType(DEFAULT_SHADING_TYPE)
{
}

Material::Material(
	Color& ambient,
	Color& diffuse,
	Color& specular,
	ShadingType shadingType)
  :
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(DEFAULT_SHININESS),
	texture(DEFAULT_TEXTURE),
	shadingType(shadingType)
{
}

Material::Material(
	Color& ambient,
	Color& diffuse,
	Color& specular,
	double shininess,
	ShadingType shadingType)
  :
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess),
	texture(DEFAULT_TEXTURE),
	shadingType(shadingType)
{
}

void Material::CalculateDefaultMaterialProperties(Color& color)
{
	ambient = Color(color * DEFAULT_AMBIENT_CONST);
	diffuse = Color(color);
	specular = Color(color * DEFAULT_SPECULAR_CONST);
}
