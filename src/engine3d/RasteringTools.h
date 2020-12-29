#pragma once

#include <vector>

namespace softengine
{
	class Vector2D;
	class Vector3D;
	class Vector4D;
	class Vertex3D;
	class Vertex4D;
	class Material;
	class Camera;
	class RenderSurface;
	class SceneLighting;
	enum class DepthCheckMode;
	struct PipelineConfiguration;

	class RasteringTools
	{
	public:
		RasteringTools() = delete;

		static bool PassesClipTest(Vertex4D& v1);

		static void TranformToRasterSpace(
			Vertex4D& vertex,
			Camera& camera
		);

		static bool PassesDepthCheck(
			RenderSurface& surface,
			Vector4D& fragment,
			DepthCheckMode depthCheckMode
		);

		static void PointRasteriser(
			RenderSurface& surface,
			PipelineConfiguration& pipelineConfiguration,
			Camera& camera,
			Vertex4D& vertex,
			SceneLighting& lights
		);

		static void LineRasteriser(
			RenderSurface& surface,
			PipelineConfiguration& pipelineConfiguration,
			Camera& camera,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			SceneLighting& lights
		);

		static void TriangleRasteriser(
			RenderSurface& surface,
			PipelineConfiguration& pipelineConfiguration,
			Camera& camera,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			Vertex4D& vertex3,
			Vertex4D& oV1,
			Vertex4D& oV2,
			Vertex4D& oV3,
			Material& material,
			SceneLighting& lights
		);
	};
}