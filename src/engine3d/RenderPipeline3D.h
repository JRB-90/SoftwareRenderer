#pragma once

#include "DrawType.h"
#include <memory>
#include <vector>

namespace softengine
{
	class RenderSurface;
	class VBO3D;
	class Matrix4;
	class Camera;
	class Vector4D;
	class Color;
	class Texture;
	class SceneLighting;
	struct Vertex3D;
	struct Vertex4D;
	enum class BackFaceCullingMode;
	enum class DepthCheckMode;
	enum class ShadingType;

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
			Texture& texture,
			SceneLighting& lights,
			ShadingType shadingType
		);

		void RunPoints(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			SceneLighting& lights
		);

		void RunLines(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			SceneLighting& lights
		);

		void RunTriangles(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Texture& texture,
			SceneLighting& lights,
			ShadingType shadingType
		);

		void RunQuads(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Texture& texture,
			SceneLighting& lights,
			ShadingType shadingType
		);

		Vertex4D VertexShader(
			RenderSurface& surface,
			Vertex3D& vertex,
			Matrix4& model,
			Camera& camera
		);

		void PointRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex,
			SceneLighting& lights
		);

		void LineRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			SceneLighting& lights
		);

		void TriangleRasteriser(
			RenderSurface& surface,
			Vertex4D& vertex1,
			Vertex4D& vertex2,
			Vertex4D& vertex3,
			Vertex4D& oV1,
			Vertex4D& oV2,
			Vertex4D& oV3,
			Texture& texture,
			SceneLighting& lights,
			ShadingType shadingType
		);

		void PixelShader(
			RenderSurface& surface,
			Vector4D& fragment,
			Vector4D& normal,
			Color& color,
			Vector4D& faceNormal,
			SceneLighting& lights,
			ShadingType shadingType
		);

		void PixelShaderFlat(
			RenderSurface& surface,
			Vector4D& fragment,
			Vector4D& normal,
			Color& color,
			Vector4D& faceNormal,
			SceneLighting& lights
		);

		void PixelShaderPhong(
			RenderSurface& surface,
			Vector4D& fragment,
			Vector4D& normal,
			Color& color,
			SceneLighting& lights
		);

	private:
		bool isWireFrame;
		DrawType drawType;
		BackFaceCullingMode cullingMode;
		DepthCheckMode depthCheckMode;
	};
}