#pragma once

#include "DrawType.h"
#include <memory>

namespace softengine
{
	class RenderSurface;
	class VBO3D;
	class Matrix4;
	class Camera;
	class Vector4D;
	struct Vertex3D;
	struct Vertex4D;
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

		Vertex4D VertexShader(
			RenderSurface& surface,
			Vertex3D& vertex,
			Matrix4& model,
			Camera& camera
		);

		bool PassesClipTest(Vertex4D& v1);

		void TranformToRasterSpace(
			Vertex4D& vertex,
			Camera& camera
		);

		void PointRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex
		);

		void LineRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex1,
			Vertex4D& vertex2
		);

		void TriangleRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			Vertex4D& vertex3,
			Vertex4D& oV1,
			Vertex4D& oV2,
			Vertex4D& oV3,
			Texture& texture
		);

		void PixelShader(
			RenderSurface& surface,
			Vector4D& fragment,
			Vector4D& normal,
			Color& color
		);

	private:
		bool isWireFrame;
		DrawType drawType;
		BackFaceCullingMode cullingMode;
		DepthCheckMode depthCheckMode;
	};
}