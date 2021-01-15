#pragma once

#include "DrawType.h"
#include "PipelineConfiguration3D.h"
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
	class Material;
	class SceneLighting;
	struct Vertex3D;
	struct Vertex4D;

	class RenderPipeline3D
	{
	public:
		RenderPipeline3D(
			PipelineConfiguration pipelineConfiguration
		);

		PipelineConfiguration& Configuration() { return pipelineConfiguration; }
		void Configuration(PipelineConfiguration& pipelineConfiguration) { this->pipelineConfiguration = pipelineConfiguration; }

		void Run(
			RenderSurface& surface,
			DrawType drawType,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Material& material,
			SceneLighting& lights
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
			Material& material,
			SceneLighting& lights
		);

		void RunTriangle(
			RenderSurface& surface,
			VBO3D& vbo,
			int& index,
			Matrix4& mvp,
			Camera& camera,
			Material& material,
			SceneLighting& lights
		);

	private:
		PipelineConfiguration pipelineConfiguration;
	};
}