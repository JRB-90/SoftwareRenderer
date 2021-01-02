#include "ShaderTools.h"

#include "RenderSurface.h"
#include "Color.h"
#include "Material.h"
#include "Vector4D.h"
#include "Vertex3D.h"
#include "Vertex4D.h"
#include "Matrix4.h"
#include "Camera.h"
#include "SceneLighting.h"
#include "RasteringTools.h"
#include "PipelineConfiguration3D.h"

using namespace softengine;

Vertex4D ShaderTools::SimpleVertexShader(
	RenderSurface& surface, 
	Vertex3D& vertex, 
	Matrix4& mvp)
{
	Vector4D vertPosition(
		vertex.Position.X(),
		vertex.Position.Y(),
		vertex.Position.Z(),
		1.0
	);

	Vector4D vertNormal(
		vertex.Normal.X(),
		vertex.Normal.Y(),
		vertex.Normal.Z(),
		0.0
	);

	vertPosition = vertPosition * mvp;
	vertNormal = vertNormal * mvp;

	return
		Vertex4D(
			vertPosition,
			Vector4D(
				vertex.UVCoord.X(),
				vertex.UVCoord.Y(),
				0.0,
				1.0
			),
			vertNormal.Normalised(),
			vertex.VertColor
		);
}

void ShaderTools::SimpleVertexShader(
	VertexShaderIn& in,
	VertexShaderOut& out)
{
	Vector4D vertPosition(
		in.vertex->Position.X(),
		in.vertex->Position.Y(),
		in.vertex->Position.Z(),
		1.0
	);

	Vector4D vertNormal(
		in.vertex->Normal.X(),
		in.vertex->Normal.Y(),
		in.vertex->Normal.Z(),
		0.0
	);

	Matrix4 MVP = in.camera->ProjectionMatrix() * in.camera->ViewMatrix() * (*in.model);
	vertPosition = vertPosition * MVP;
	vertNormal = vertNormal * MVP;

	out.vertex =
		Vertex4D(
			vertPosition,
			Vector4D(
				in.vertex->UVCoord.X(),
				in.vertex->UVCoord.Y(),
				0.0,
				1.0
			),
			vertNormal.Normalised(),
			in.vertex->VertColor
		);
}

void ShaderTools::PixelShader(
	RenderSurface& surface,
	Camera& camera,
	Vector4D& fragment,
	Vector4D& position,
	Vector4D& normal,
	Vector4D& faceNormal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights,
	DepthCheckMode depthCheckMode,
	Profiler& profiler)
{
	profiler.ResetTimer();
	switch (material.GetShadingType())
	{
	case ShadingType::None:
		surface.SetPixelValue(
			fragment.X(),
			fragment.Y(),
			interpolatedColor
		);
		profiler.AddTiming("Shader None");
		break;
	case ShadingType::Normal:
		PixelShaderNormal(
			surface,
			camera,
			fragment,
			normal,
			faceNormal,
			interpolatedColor,
			material,
			lights
		);
		profiler.AddTiming("Shader Normal");
		break;
	case ShadingType::Flat:
		PixelShaderPhong(
			surface,
			camera,
			fragment,
			position,
			faceNormal,
			interpolatedColor,
			material,
			lights
		);
		profiler.AddTiming("Shader Flat");
		break;
	case ShadingType::Phong:
		PixelShaderPhong(
			surface,
			camera,
			fragment,
			position,
			normal,
			interpolatedColor,
			material,
			lights
		);
		profiler.AddTiming("Shader Phong");
		break;
	default:
		break;
	}
}

void ShaderTools::PixelShaderNormal(RenderSurface& surface,
	Camera& camera,
	Vector4D& fragment,
	Vector4D& normal,
	Vector4D& faceNormal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights)
{

	surface.SetPixelValue(
		fragment.X(),
		fragment.Y(),
		Color(
			(normal.X() + 1.0) / 2.0,
			(normal.Y() + 1.0) / 2.0,
			(normal.Z() + 1.0) / 2.0,
			1.0
		)
	);
}

void ShaderTools::PixelShaderPhong(
	RenderSurface& surface,
	Camera& camera,
	Vector4D& fragment,
	Vector4D& position,
	Vector4D& normal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights)
{
	Vector3D frag = Vector3D(fragment.X(), fragment.Y(), fragment.Z());
	Vector3D pos = Vector3D(position.X(), position.Y(), position.Z());
	Vector3D viewDir = (camera.Position().Translation() - pos).Normalised();
	Vector3D norm = Vector3D(normal.X(), normal.Y(), normal.Z()).Normalised();

	Color matAmbient = material.Ambient();
	Color matDiffuse = material.Difffuse();
	Color matSpecular = material.Specular();
	double shininess = material.Shininess();

	if (material.GetTexture().Width() > 0 &&
		material.GetTexture().Height() > 0)
	{
		matAmbient = interpolatedColor * 0.4;
		matDiffuse = interpolatedColor;
		matSpecular = interpolatedColor * 1.3;
	}

	Color ambientLight = lights.GetAmbientLight().GetColor() * lights.GetAmbientLight().Strength();

	Color finalColor = matAmbient * ambientLight;

	for (size_t i = 0; i < lights.GetDirectionalLights().size(); i++)
	{
		finalColor = 
			finalColor + 
			CalculateLight(
				lights.GetDirectionalLights()[i],
				pos,
				norm,
				viewDir,
				matDiffuse,
				matSpecular,
				shininess
			);
	}

	for (size_t i = 0; i < lights.GetPointsLights().size(); i++)
	{
		finalColor =
			finalColor +
			CalculateLight(
				lights.GetPointsLights()[i],
				pos,
				norm,
				viewDir,
				matDiffuse,
				matSpecular,
				shininess
			);
	}

	surface.SetPixelValue(
		fragment.X(),
		fragment.Y(),
		finalColor
	);
}

Color ShaderTools::CalculateLight(
	Light& light,
	Vector3D& pos,
	Vector3D& normal,
	Vector3D viewDir,
	Color& matDiffuse,
	Color& matSpecular,
	double shininess)
{
	double attenuation;
	Vector3D lightDir;

	if (light.GetLightType() == LightType::Directional)
	{
		attenuation = 1.0;
		lightDir = light.Direction().Normalised() * -1.0;
	}
	else
	{
		lightDir = (light.Position() - pos).Normalised();
		double distance = lightDir.Length();
		attenuation = 
			1.0 / 
			(
				light.GetAttenuation().Constant +
				light.GetAttenuation().Linear * distance +
				light.GetAttenuation().Quadratic * distance * distance
			);
	}

	double intensity =
		std::max(
			normal.Dot(lightDir),
			0.0
		);

	Color diffuse = light.GetColor() * matDiffuse * attenuation * intensity;
	Color specular;

	if (normal.Dot(lightDir) < 0.0)
	{
		specular = Color(0.0, 0.0, 0.0, 1.0);
	}
	else
	{
		specular =
			light.GetColor() *
			matSpecular *
			attenuation*
			std::pow(std::max(0.0, Reflect(lightDir, normal).Dot(viewDir)), shininess);
	}

	return diffuse + specular;
}

Vector3D ShaderTools::Reflect(
	Vector3D v1, 
	Vector3D v2)
{
	return v1 - (v2 * 2.0 * v2.Dot(v1));
}
