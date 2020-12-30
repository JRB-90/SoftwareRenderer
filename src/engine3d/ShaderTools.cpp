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
	Matrix4& model, 
	Camera& camera)
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

	Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;
	vertPosition = vertPosition * MVP;
	vertNormal = vertNormal * MVP;

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
	Vector4D& normal,
	Vector4D& faceNormal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights,
	DepthCheckMode depthCheckMode)
{
	if (!RasteringTools::PassesDepthCheck(
		surface,
		fragment,
		depthCheckMode)
		)
	{
		return;
	}

	switch (material.GetShadingType())
	{
	case ShadingType::None:
		surface.SetPixelValue(
			fragment.X(),
			fragment.Y(),
			interpolatedColor
		);
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
		break;
	case ShadingType::Flat:
		PixelShaderFlat(
			surface,
			camera,
			fragment,
			normal,
			faceNormal,
			interpolatedColor,
			material,
			lights
		);
		break;
	case ShadingType::Phong:
		PixelShaderPhong(
			surface,
			camera,
			fragment,
			normal,
			interpolatedColor,
			material,
			lights
		);
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

// TODO - Change these to only have a normal attribute and get the calling function to calc the
//        flat normal and pass it in as the normal, that I don't have to duplicate the flat
//        and phong?

void ShaderTools::PixelShaderFlat(
	RenderSurface& surface,
	Camera& camera,
	Vector4D& fragment,
	Vector4D& normal,
	Vector4D& faceNormal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights)
{
	Color matAmbient = material.Ambient();
	Color matDiffuse = material.Difffuse();

	if (material.GetTexture().Height() > 0 &&
		material.GetTexture().Width() > 0)
	{
		matAmbient = interpolatedColor * 0.4;
		matDiffuse = interpolatedColor;
	}

	Color ambientLight = lights.GetAmbientLight().GetColor() * lights.GetAmbientLight().Strength();
	Vector3D flatNormal = Vector3D(faceNormal.X(), faceNormal.Y(), faceNormal.Z()).Normalised();
	Vector3D lightDir = lights.GetDirectionalLights()[0].Direction().Normalised() * -1.0;

	double intensity =
		std::max(
			flatNormal.Dot(lightDir),
			0.0
		);

	if (intensity > 0.5)
	{
		int test = 0;
	}

	Color diffuseLight = lights.GetDirectionalLights()[0].GetColor() * intensity;

	Color ambient = matAmbient * ambientLight;
	Color diffuse = matDiffuse * diffuseLight;
	Color finalColor = ambient + diffuse;

	surface.SetPixelValue(
		fragment.X(),
		fragment.Y(),
		finalColor
	);
}

void ShaderTools::PixelShaderPhong(
	RenderSurface& surface,
	Camera& camera,
	Vector4D& fragment,
	Vector4D& normal,
	Color& interpolatedColor,
	Material& material,
	SceneLighting& lights)
{
	Color matAmbient = material.Ambient();
	Color matDiffuse = material.Difffuse();

	if (material.GetTexture().Height() > 0 &&
		material.GetTexture().Width() > 0)
	{
		matAmbient = interpolatedColor * 0.4;
		matDiffuse = interpolatedColor;
	}

	Color ambientLight = lights.GetAmbientLight().GetColor() * lights.GetAmbientLight().Strength();
	Vector3D norm = Vector3D(normal.X(), normal.Y(), normal.Z());
	Vector3D lightDir = lights.GetDirectionalLights()[0].Direction().Normalised() * -1.0;

	double intensity =
		std::max(
			norm.Dot(lightDir),
			0.0
		);

	if (intensity > 0.5)
	{
		int test = 0;
	}

	Color diffuseLight = lights.GetDirectionalLights()[0].GetColor() * intensity;

	Color ambient = matAmbient * ambientLight;
	Color diffuse = matDiffuse * diffuseLight;
	Color finalColor = ambient + diffuse;

	surface.SetPixelValue(
		fragment.X(),
		fragment.Y(),
		finalColor
	);
}
