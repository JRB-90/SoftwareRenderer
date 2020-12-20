#pragma once

#include <vector>

namespace softengine
{
	class Vector2D;
	class Vector3D;
	class Vertex3D;
	class Color;
	class Texture;

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

		static Vector3D FindBaryCentricCoords(
			Vector2D& v1,
			Vector2D& v2,
			Vector2D& v3,
			Vector2D& pos
		);

		static Vector3D FindBaryCentricCoords(
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Vector2D& pos
		);

		static Color InterpolateColor(
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Vector3D& pos
		);

		static Color InterpolateTexture(
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Vector3D& pos,
			Texture& texture
		);
	};
}