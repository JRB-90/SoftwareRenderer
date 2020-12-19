#pragma once

#include "RenderSurface.h"
#include "Mesh3D.h"
#include "Camera.h"
#include "Texture.h"

namespace softengine
{
	class Primitive3DRenderer
	{
	public:
		Primitive3DRenderer() = delete;

		static void RenderMesh(
			RenderSurface& surface,
			Mesh3D& mesh,
			Camera& camera
		);

		static void RenderVertex(
			RenderSurface& surface,
			Vertex3D& vertex
		);

		static void RenderLine(
			RenderSurface& surface,
			Vertex3D& v1,
			Vertex3D& v2
		);

		static void RenderTriangle(
			RenderSurface& surface,
			Camera& camera,
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Texture& texture = Texture()
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

		static bool IsValidSpritePixel(Color& color);

		static Vertex3D VertexShader(
			Vertex3D& vertex,
			Frame3D& model,
			Camera& camera
		);

		static Color PixelShader(
			Color pixelColor,
			Vector3D pixelPosition,
			Camera& camera
		);
	};
}