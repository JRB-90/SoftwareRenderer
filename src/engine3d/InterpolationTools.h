#pragma once

#include "Vector4D.h"
#include "Color.h"
#include <vector>

namespace softengine
{
	class Vector2D;
	class Vector3D;
	class Vertex3D;
	class Vertex4D;
	class Texture;
	class Material;
	struct RasterFragment;

	struct InterpolatedFragment
	{
		Vector4D Fragment;
		Vector4D Position;
		Vector4D Normal;
		Vector4D TexCoords;
		Color FragColor;

		InterpolatedFragment(
			Vector4D& fragment,
			Vector4D& position,
			Vector4D& normal,
			Vector4D& texCoords,
			Color& fragColor)
		{
			this->Fragment = fragment;
			this->Position = position;
			this->Normal = normal;
			this->TexCoords = texCoords;
			this->FragColor = fragColor;
		}
	};

	class InterpolationTools
	{
	public:
		InterpolationTools() = delete;

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

		static Vector4D InterpolateVec4(
			Vector3D& baryCoords,
			Vector4D& v1,
			Vector4D& v2,
			Vector4D& v3
		);

		static Vector4D InterpolateVec4PerspCorrect(
			Vector3D& baryCoords,
			Vector4D& v1,
			Vector4D& v2,
			Vector4D& v3,
			Vector4D& fragment
		);

		static Vector4D InterpolateNormal(
			Vector3D& baryCoords,
			Vertex4D& v1,
			Vertex4D& v2,
			Vertex4D& v3,
			bool perspectiveCorrect = true
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

		static InterpolatedFragment InterpolateFragment(
			RasterFragment fragment,
			Vertex4D& vertex0,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			Vertex4D& oV0,
			Vertex4D& oV1,
			Vertex4D& oV2,
			Vector4D& vc0,
			Vector4D& vc1,
			Vector4D& vc2,
			Material& material
		);

		static Vector4D CalculateFaceNormal(
			Vector4D v0,
			Vector4D v1,
			Vector4D v2
		);
	};
}