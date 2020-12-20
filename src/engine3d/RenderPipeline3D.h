#pragma once

#include "DrawType.h"
#include <memory>

namespace softengine
{
	class RenderSurface;
	class VBO3D;
	class Matrix4;
	class Camera;
	class Vector3D;
	struct Vertex3D;
	class Vector4D;
	class Color;
	class Texture;
	enum class BackFaceCullingMode;
	enum class DepthCheckMode;

	class RenderPipeline3D
	{
	public:
		RenderPipeline3D(
			bool isWireFrame,
			DrawType drawType,
			BackFaceCullingMode cullingMode,
			DepthCheckMode depthCheckMode
		);

		bool GetIsWireFrame() { return isWireFrame; }
		void SetIsWireFrame(bool isWireFrame) { this->isWireFrame = isWireFrame; }
		DrawType GetDrawType() { return drawType; }
		void SetDrawType(DrawType drawType) { this->drawType = drawType; }
		BackFaceCullingMode GetCullingMode() { return cullingMode; }
		void SetCullingMode(BackFaceCullingMode cullingMode) { this->cullingMode = cullingMode; }
		DepthCheckMode GetDepthCheckMode() { return depthCheckMode; }
		void SetDepthCheckMode(DepthCheckMode cullingMode) { this->depthCheckMode = depthCheckMode; }

		void Run(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Texture& texture
		);

		void RunPoints(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera
		);

		void RunLines(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera
		);

		void RunTriangles(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Texture& texture
		);

		void RunQuads(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Texture& texture
		);

		Vector4D VertexShader(
			RenderSurface& surface,
			Vertex3D& vertex,
			Matrix4& model,
			Camera& camera
		);

		bool PassesClipTest(Vector4D& v1);

		Vector3D TranformToRasterSpace(
			Vector4D& vertex,
			Camera& camera
		);

		void PointRasteriser(
			RenderSurface& surface,
			Vertex3D& vertex
		);

		void LineRasteriser(
			RenderSurface& surface,
			Vertex3D& vertex1,
			Vertex3D& vertex2
		);

		void TriangleRasteriser(
			RenderSurface& surface,
			Vertex3D& vertex1,
			Vertex3D& vertex2,
			Vertex3D& vertex3,
			Texture& texture
		);

		void PixelShader(
			RenderSurface& surface,
			Vector3D& fragment,
			Vector3D& normal,
			Color& color
		);

	private:
		bool isWireFrame;
		DrawType drawType;
		BackFaceCullingMode cullingMode;
		DepthCheckMode depthCheckMode;
	};
}