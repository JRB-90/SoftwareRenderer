#pragma once

#include "Vector3D.h"
#include "Vector4D.h"
#include <vector>

namespace softengine
{
	class Vector2D;
	class Vertex3D;
	class Vertex4D;
	class Material;
	class Camera;
	class RenderSurface;
	class SceneLighting;
	enum class DepthCheckMode;
	struct PipelineConfiguration;
	struct VertexShaderOut;

	struct PointRasteriserIn
	{
		RenderSurface* surface;
		PipelineConfiguration* pipelineConfiguration;
		Camera* camera;
		Material* material;
		SceneLighting* lights;
		Vertex4D* vertex1;
		Vertex4D* oV1;

		PointRasteriserIn(
			RenderSurface* surface,
			PipelineConfiguration* pipelineConfiguration,
			Camera* camera,
			Material* material,
			SceneLighting* lights,
			Vertex4D* vertex1,
			Vertex4D* oV1
		)
		  :
			surface(surface),
			pipelineConfiguration(pipelineConfiguration),
			camera(camera),
			material(material),
			lights(lights),
			vertex1(vertex1),
			oV1(oV1)
		{
		}
	};

	struct LineRasteriserIn
	{
		RenderSurface* surface;
		PipelineConfiguration* pipelineConfiguration;
		Camera* camera;
		Material* material;
		SceneLighting* lights;
		Vertex4D* vertex1;
		Vertex4D* vertex2;
		Vertex4D* oV1;
		Vertex4D* oV2;

		LineRasteriserIn(
			RenderSurface* surface,
			PipelineConfiguration* pipelineConfiguration,
			Camera* camera,
			Material* material,
			SceneLighting* lights,
			Vertex4D* vertex1,
			Vertex4D* vertex2,
			Vertex4D* oV1,
			Vertex4D* oV2
		)
		  :
			surface(surface),
			pipelineConfiguration(pipelineConfiguration),
			camera(camera),
			material(material),
			lights(lights),
			vertex1(vertex1),
			vertex2(vertex2),
			oV1(oV1),
			oV2(oV2)
		{
		}
	};

	struct TriRasteriserIn
	{
		RenderSurface* surface;
		PipelineConfiguration* pipelineConfiguration;
		Camera* camera;
		Material* material;
		SceneLighting* lights;
		Vertex4D* vertex1;
		Vertex4D* vertex2;
		Vertex4D* vertex3;
		Vertex4D* oV1;
		Vertex4D* oV2;
		Vertex4D* oV3;

		TriRasteriserIn(
			RenderSurface* surface,
			PipelineConfiguration* pipelineConfiguration,
			Camera* camera,
			Material* material,
			SceneLighting* lights,
			Vertex4D* vertex1,
			Vertex4D* vertex2,
			Vertex4D* vertex3,
			Vertex4D* oV1,
			Vertex4D* oV2,
			Vertex4D* oV3
		)
		  :
			surface(surface),
			pipelineConfiguration(pipelineConfiguration),
			camera(camera),
			material(material),
			lights(lights),
			vertex1(vertex1),
			vertex2(vertex2),
			vertex3(vertex3),
			oV1(oV1),
			oV2(oV2),
			oV3(oV3)
		{
		}
	};

	struct RasterFragment
	{
		Vector3D BaryCoords;
		Vector4D Fragment;

		RasterFragment(
			Vector3D& baryCoords,
			Vector4D& fragment)
		{
			this->BaryCoords = baryCoords;
			this->Fragment = fragment;
		}
	};

	class RasteringTools
	{
	public:
		RasteringTools() = delete;

		static bool PassesClipTest(Vertex4D& v1);

		static bool PassesClipTest(VertexShaderOut& out);

		static void TranformToRasterSpace(
			Vertex4D& vertex,
			Camera& camera
		);

		static void TranformToRasterSpace(
			VertexShaderOut& out,
			Camera& camera
		);

		static bool PassesDepthCheck(
			RenderSurface& surface,
			Vector3D& fragment,
			DepthCheckMode depthCheckMode
		);

		static void PointRasteriser(
			RenderSurface& surface,
			PipelineConfiguration& pipelineConfiguration,
			Camera& camera,
			Vertex4D& vertex,
			SceneLighting& lights
		);

		static void PointRasteriser(
			PointRasteriserIn in
		);

		static void LineRasteriser(
			RenderSurface& surface,
			PipelineConfiguration& pipelineConfiguration,
			Camera& camera,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			SceneLighting& lights
		);

		static std::vector<RasterFragment> TriangleRasteriser(
			PipelineConfiguration& pipelineConfiguration,
			Vertex4D& vertex0,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			Vertex4D& oV0,
			Vertex4D& oV1,
			Vertex4D& oV2
		);
	};
}