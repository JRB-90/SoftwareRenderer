#pragma once

#include <vector>

namespace softengine
{
	class Vector2D;
	class Vector3D;
	class Vector4D;
	class Vertex3D;
	class Vertex4D;
	class Color;
	class Texture;
	class Camera;
	class RenderSurface;
	enum class DepthCheckMode;

	class RasteringTools
	{
	public:
		RasteringTools() = delete;

		static std::vector<int> InterpolateXPixelValues(
			int x0,
			int y0,
			int x1,
			int y1
		);

		static std::vector<int> InterpolateYPixelValues(
			int x0,
			int y0,
			int x1,
			int y1
		);

		static Vector3D FindBaryCentricFactors(
			Vector2D& v1,
			Vector2D& v2,
			Vector2D& v3,
			Vector2D& pos
		);

		static Vector3D FindBaryCentricFactors(
			Vector3D& v1,
			Vector3D& v2,
			Vector3D& v3,
			Vector3D& pos
		);

		static Vector3D FindBaryCentricFactors(
			Vector4D& v1,
			Vector4D& v2,
			Vector4D& v3,
			Vector4D& pos
		);

		static Vector3D FindBaryCentricFactors(
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Vector2D& pos
		);

		static Color InterpolateColor(
			Vector3D& baryCoords,
			Vertex4D& v1,
			Vertex4D& v2,
			Vertex4D& v3,
			Vector4D& pos,
			bool perspectiveCorrect = true
		);

		static Color InterpolateTexture(
			Vector3D& baryCoords,
			Vertex4D& v1,
			Vertex4D& v2,
			Vertex4D& v3,
			Vector4D& pos,
			Texture& texture,
			bool perspectiveCorrect = true
		);

		static Vector4D InterpolateNormal (
			Vector3D& baryCoords,
			Vertex4D& v1,
			Vertex4D& v2,
			Vertex4D& v3,
			Vector4D& pos,
			bool perspectiveCorrect = true
		);

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
	};
}