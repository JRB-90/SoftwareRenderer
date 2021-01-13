#pragma once

#include "DrawType.h"
#include "PipelineConfiguration3D.h"
#include "Vertex3D.h"
#include "Matrix4.h"
#include "Camera.h"
#include "Material.h"
#include "SceneLighting.h"
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

namespace softengine
{
	class RenderSurface;
	class VBO3D;
	class Vector4D;
	class Color;
	struct Vertex4D;

	struct RenderJob
	{
		RenderSurface* Surface;
		Vertex3D V1;
		Vertex3D V2;
		Vertex3D V3;
		Matrix4 MVP;
		Camera Cam;
		std::shared_ptr<Material> Mat;
		std::shared_ptr<SceneLighting> Lights;

		RenderJob(
			RenderSurface* surface,
			Vertex3D& v1,
			Vertex3D& v2,
			Vertex3D& v3,
			Matrix4& mvp,
			Camera& cam,
			std::shared_ptr<Material>& mat,
			std::shared_ptr<SceneLighting>& lights)
		{
			this->Surface = surface;
			this->V1 = v1;
			this->V2 = v2;
			this->V3 = v3;
			this->MVP = mvp;
			this->Cam = cam;
			this->Mat = mat;
			this->Lights = lights;
		}
	};

	class RenderPipeline3D
	{
	public:
		RenderPipeline3D(
			PipelineConfiguration pipelineConfiguration
		);
		~RenderPipeline3D();

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

		void RunQuads(
			RenderSurface& surface,
			VBO3D& vbo,
			Matrix4& model,
			Camera& camera,
			Material& material,
			SceneLighting& lights
		);

	private:
		PipelineConfiguration pipelineConfiguration;
		// TODO - Make a queue containing a custom type that stores all
		//        the data needed to render a specific triangle
		std::queue<RenderJob> renderQueue;
		std::vector<std::thread> threadPool;
		std::recursive_mutex renderQueueMutex;
		std::atomic<bool> isRenderQueueRunning;

		void AddRenderJob(RenderJob& renderJob);
		void AwaitJobCompletion();
		void RenderQueueLoop();

		void RunTriangle(
			RenderSurface& surface,
			RenderJob& job
		);
	};
}