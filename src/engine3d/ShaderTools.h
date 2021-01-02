#pragma once

#include "Profiler.h"
#include "Vertex4D.h"
#include <iostream>

namespace softengine
{
	class RenderSurface;
	class Color;
	class Material;
	class Vector4D;
	class Vertex3D;
	class Matrix4;
	class Camera;
	class Light;
	class SceneLighting;
	enum class DepthCheckMode;

	struct VertexShaderIn
	{
		RenderSurface* surface;
		Vertex3D* vertex;
		Matrix4* model;
		Camera* camera;

		VertexShaderIn()
	      :
			surface(NULL),
			vertex(NULL),
			model(NULL),
			camera(NULL)
		{
		}

		VertexShaderIn(
			RenderSurface* surface,
			Vertex3D* vertex,
			Matrix4* model,
			Camera* camera)
	      :
			surface(surface),
			vertex(vertex),
			model(model),
			camera(camera)
		{
		}
	};

	struct VertexShaderOut
	{
		Vertex4D vertex;

		VertexShaderOut()
		{
		}

		VertexShaderOut(Vertex4D vertex)
		  :
			vertex(vertex)
		{
		}
	};

	struct Fragment
	{
		Vector3D position;
		Vector3D normal;
		Vector3D faceNormal;
		Color color;
	};

	class ShaderTools
	{
	public:
		ShaderTools() = delete;

		static Vertex4D SimpleVertexShader(
			RenderSurface& surface,
			Vertex3D& vertex,
			Matrix4& mvp
		);

		static void SimpleVertexShader(
			VertexShaderIn& in,
			VertexShaderOut& out
		);

		static void PixelShader(
			RenderSurface& surface,
			Camera& camera,
			Vector4D& fragment,
			Vector4D& normal,
			Vector4D& faceNormal,
			Color& interpolatedColor,
			Material& material,
			SceneLighting& lights,
			DepthCheckMode depthCheckMode,
			Profiler& profiler
		);

		static void PixelShader(
			RenderSurface& surface,
			Fragment& fragment,
			Material& material,
			SceneLighting& lights,
			Profiler& profiler
		);

		static void PixelShaderNormal(
			RenderSurface& surface,
			Camera& camera,
			Vector4D& fragment,
			Vector4D& normal,
			Vector4D& faceNormal,
			Color& interpolatedColor,
			Material& material,
			SceneLighting& lights
		);

		static void PixelShaderFlat(
			RenderSurface& surface,
			Camera& camera,
			Vector4D& fragment,
			Vector4D& normal,
			Vector4D& faceNormal,
			Color& interpolatedColor,
			Material& material,
			SceneLighting& lights
		);

		static void PixelShaderPhong(
			RenderSurface& surface,
			Camera& camera,
			Vector4D& fragment,
			Vector4D& normal,
			Color& interpolatedColor,
			Material& material,
			SceneLighting& lights
		);

		static Color CalculateLight(
			Light& light,
			Vector3D& pos,
			Vector3D& normal,
			Vector3D viewDir,
			Color& matDiffuse,
			Color& matSpecular,
			double shininess
		);

		static Vector3D Reflect(
			Vector3D v1,
			Vector3D v2
		);
	};
}