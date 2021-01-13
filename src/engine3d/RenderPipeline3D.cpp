#include "RenderPipeline3D.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "VBO3D.h"
#include "Vector3D.h"
#include "Vertex3D.h"
#include "Vector4D.h"
#include "Vertex4D.h"
#include "Color.h"
#include "Texture.h"
#include "RasteringTools.h"
#include "InterpolationTools.h"
#include "ShadingType.h"
#include "ShaderTools.h"
#include "Profiler.h"

#include <iostream>
#include <cmath>
#include <functional>
#include <chrono>

using namespace softengine;

RenderPipeline3D::RenderPipeline3D(
	PipelineConfiguration pipelineConfiguration)
  :
	pipelineConfiguration(pipelineConfiguration),
	isRenderQueueRunning(true)
{
	//int availableThreads = std::thread::hardware_concurrency();
	int availableThreads = 1;

	for (int i = 0; i < availableThreads; i++)
	{
		threadPool.push_back(
			std::thread(
				&RenderPipeline3D::RenderQueueLoop,
				this
			)
		);
	}
}

RenderPipeline3D::~RenderPipeline3D()
{
	isRenderQueueRunning = false;

	for (std::thread& thd : threadPool)
	{
		thd.join();
	}
	threadPool.clear();
}

void RenderPipeline3D::Run(
	RenderSurface& surface,
	DrawType drawType,
	VBO3D& vbo, 
	Matrix4& model,
	Camera& camera,
	Material& material,
	SceneLighting& lights)
{
	if (pipelineConfiguration.wireframeModeEnabled)
	{
		RunLines(
			surface,
			vbo,
			model,
			camera,
			lights
		);

		return;
	}

	switch (drawType)
	{
	case DrawType::Points:
		RunPoints(
			surface,
			vbo,
			model,
			camera,
			lights
		);
		break;
	case DrawType::Lines:
		RunLines(
			surface,
			vbo,
			model,
			camera,
			lights
		);
		break;
	case DrawType::Triangles:
		RunTriangles(
			surface,
			vbo,
			model,
			camera,
			material,
			lights
		);
		break;
	case DrawType::Quads:
		RunQuads(
			surface,
			vbo,
			model,
			camera,
			material,
			lights
		);
		break;
	default:
		return;
	}
}

void RenderPipeline3D::RunPoints(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	SceneLighting& lights)
{
	Profiler pipelineProfiler;
	Profiler pixelProfiler;

	for (size_t i = 0; i < vbo.IndicesSize(); i++)
	{
		pipelineProfiler.ResetTimer();

		Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

		Vertex4D vert = 
			ShaderTools::SimpleVertexShader(
				vbo.Vertices(vbo.Indices(i)),
				MVP
			);

		//VertexShaderIn vertIn(
		//	&surface,
		//	&vbo.Vertices(vbo.Indices(i)),
		//	&model,
		//	&camera
		//);
		//VertexShaderOut vertOut;
		//ShaderTools::SimpleVertexShader(vertIn, vertOut);

		pipelineProfiler.AddTiming("Vertex Shader");

		if (!RasteringTools::PassesClipTest(vert))
		{
			continue;
		}

		//if (RasteringTools::PassesClipTest(vertOut))
		//{
		//	continue;
		//}

		pipelineProfiler.AddTiming("Clip Test");

		RasteringTools::TranformToRasterSpace(
			vert,
			camera
		);

		//RasteringTools::TranformToRasterSpace(
		//	vertOut,
		//	camera
		//);

		pipelineProfiler.AddTiming("Raster Space");

		RasteringTools::PointRasteriser(
			surface,
			pipelineConfiguration,
			camera,
			vert,
			lights,
			pixelProfiler
		);

		//Vertex4D oV1(
		//	vbo.Vertices(vbo.Indices(i)).Position
		//);
		//PointRasteriserIn rastIn(
		//	&surface,
		//	&pipelineConfiguration,
		//	&camera,
		//	&Material(),
		//	&lights,
		//	&vertOut.vertex,
		//	&oV1
		//);
		//RasteringTools::PointRasteriser(rastIn);

		pipelineProfiler.AddTiming("Point Raster");
	}

	pixelProfiler.PrintTimings();
	pipelineProfiler.PrintTimings();
}

void RenderPipeline3D::RunLines(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	SceneLighting& lights)
{
	Profiler pipelineProfiler;
	Profiler pixelProfiler;

	for (size_t i = 0; i < vbo.IndicesSize() - 1; i += 2)
	{
		pipelineProfiler.ResetTimer();

		Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

		Vertex4D vert1 =
			ShaderTools::SimpleVertexShader(
				vbo.Vertices(vbo.Indices(i)),
				MVP
			);
		Vertex4D vert2 =
			ShaderTools::SimpleVertexShader(
				vbo.Vertices(vbo.Indices(i + 1)),
				MVP
			);

		pipelineProfiler.AddTiming("Vertex Shader");

		if (!RasteringTools::PassesClipTest(vert1) &&
			!RasteringTools::PassesClipTest(vert2))
		{
			continue;
		}

		pipelineProfiler.AddTiming("Clip Test");

		RasteringTools::TranformToRasterSpace(
			vert1,
			camera
		);

		RasteringTools::TranformToRasterSpace(
			vert2,
			camera
		);

		pipelineProfiler.AddTiming("Raster Space");

		RasteringTools::LineRasteriser(
			surface,
			pipelineConfiguration,
			camera,
			vert1,
			vert2,
			lights,
			pixelProfiler
		);

		pipelineProfiler.AddTiming("Line Raster");
	}

	pixelProfiler.PrintTimings();
	pipelineProfiler.PrintTimings();
}

int RenderTriangleCallCount = 0;

void RenderPipeline3D::RunTriangles(
	RenderSurface& surface,
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Material& material,
	SceneLighting& lights)
{
	//Profiler pipelineProfiler;
	//Profiler pixelProfiler;

	Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

	RenderTriangleCallCount = 0;
	RenderSurface::PixelCallCount = 0;
	RasteringTools::RasterCallCount = 0;
	std::shared_ptr<Material> mat = std::make_shared<Material>(material);
	std::shared_ptr<SceneLighting> sceneLights = std::make_shared<SceneLighting>(lights);

	for (size_t i = 0; i < vbo.IndicesSize() - 2; i += 3)
	{
		RenderJob job(
			&surface,
			vbo.Vertices(vbo.Indices(i)),
			vbo.Vertices(vbo.Indices(i + 1)),
			vbo.Vertices(vbo.Indices(i + 2)),
			MVP,
			camera,
			mat,
			sceneLights
		);

		// TODO - Look at Material copy - Texture doesn't seem to copy properly..

		//AddRenderJob(job);

		RunTriangle(
			surface,
			job
		);


		{
			//pipelineProfiler.ResetTimer();

			//Vertex4D vert1 =
			//	ShaderTools::SimpleVertexShader(
			//		vbo.Vertices(vbo.Indices(i)),
			//		MVP
			//	);
			//Vertex4D vert2 =
			//	ShaderTools::SimpleVertexShader(
			//		vbo.Vertices(vbo.Indices(i + 1)),
			//		MVP
			//	);
			//Vertex4D vert3 =
			//	ShaderTools::SimpleVertexShader(
			//		vbo.Vertices(vbo.Indices(i + 2)),
			//		MVP
			//	);

			//pipelineProfiler.AddTiming("Vertex Shader");

			//if (!RasteringTools::PassesClipTest(vert1) &&
			//	!RasteringTools::PassesClipTest(vert2) &&
			//	!RasteringTools::PassesClipTest(vert3))
			//{
			//	continue;
			//}

			//pipelineProfiler.AddTiming("Clip Test");

			//Vertex4D screenSpaceV1(vert1);
			//Vertex4D screenSpaceV2(vert2);
			//Vertex4D screenSpaceV3(vert3);

			//RasteringTools::TranformToRasterSpace(
			//	vert1,
			//	camera
			//);
			//RasteringTools::TranformToRasterSpace(
			//	vert2,
			//	camera
			//);
			//RasteringTools::TranformToRasterSpace(
			//	vert3,
			//	camera
			//);

			//pipelineProfiler.AddTiming("Raster Space");

			//RasteringTools::TriangleRasteriser3(
			//	surface,
			//	pipelineConfiguration,
			//	camera,
			//	vert1,
			//	vert2,
			//	vert3,
			//	screenSpaceV1,
			//	screenSpaceV2,
			//	screenSpaceV3,
			//	material,
			//	lights,
			//	pixelProfiler
			//);

			//pipelineProfiler.AddTiming("Tri Raster");
		}
	}

	AwaitJobCompletion();

	int i = RenderSurface::PixelCallCount;
	RenderSurface::PixelCallCount = 0;
	RenderTriangleCallCount = 0;
	RasteringTools::RasterCallCount = 0;

	//pixelProfiler.PrintTimings();
	//pipelineProfiler.PrintTimings();
}

void RenderPipeline3D::RunQuads(
	RenderSurface& surface, 
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Material& material,
	SceneLighting& lights)
{
	// TODO
}

void RenderPipeline3D::AddRenderJob(RenderJob& renderJob)
{
	std::unique_lock<std::recursive_mutex> lock(renderQueueMutex);

	renderQueue.push(renderJob);
}

void RenderPipeline3D::AwaitJobCompletion()
{
	while (true)
	{
		std::unique_lock<std::recursive_mutex> lock(renderQueueMutex);
		
		if (renderQueue.empty())
		{
			return;
		}
		else
		{
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
}

void RenderPipeline3D::RenderQueueLoop()
{
	std::unique_lock<std::recursive_mutex> lock(renderQueueMutex, std::defer_lock_t());

	while (isRenderQueueRunning)
	{
		lock.lock();

		// Pull off another job
		if (!renderQueue.empty())
		{
			RenderJob job = renderQueue.front();
			renderQueue.pop();
			lock.unlock();

			RunTriangle(
				*job.Surface,
				job
			);

			//lock.lock();
			//renderQueue.pop();
			//lock.unlock();
		}
		else
		{
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
}

void RenderPipeline3D::RunTriangle(
	RenderSurface& surface,
	RenderJob& job)
{
	Profiler pixelProfiler;

	Vertex4D vert1 =
		ShaderTools::SimpleVertexShader(
			job.V1,
			job.MVP
		);
	Vertex4D vert2 =
		ShaderTools::SimpleVertexShader(
			job.V2,
			job.MVP
		);
	Vertex4D vert3 =
		ShaderTools::SimpleVertexShader(
			job.V3,
			job.MVP
		);

	if (!RasteringTools::PassesClipTest(vert1) &&
		!RasteringTools::PassesClipTest(vert2) &&
		!RasteringTools::PassesClipTest(vert3))
	{
		return;
	}

	Vertex4D screenSpaceV1(vert1);
	Vertex4D screenSpaceV2(vert2);
	Vertex4D screenSpaceV3(vert3);

	RasteringTools::TranformToRasterSpace(
		vert1,
		job.Cam
	);
	RasteringTools::TranformToRasterSpace(
		vert2,
		job.Cam
	);
	RasteringTools::TranformToRasterSpace(
		vert3,
		job.Cam
	);

	std::vector<OutputFragment> fragments = 
		RasteringTools::TriangleRasteriser4(
			pipelineConfiguration,
			vert1,
			vert2,
			vert3,
			screenSpaceV1,
			screenSpaceV2,
			screenSpaceV3,
			*job.Mat,
			pixelProfiler
		);

	for (OutputFragment& fragment : fragments)
	{
		if (
			RasteringTools::PassesDepthCheck(
				surface,
				Vector3D(
					fragment.Position.X(), 
					fragment.Position.Y(), 
					fragment.Position.Z()
				),
				pipelineConfiguration.depthCheckMode
			)
		)
		{
			ShaderTools::PixelShader(
				surface,
				job.Cam,
				fragment.Fragment,
				fragment.Position,
				fragment.Normal,
				fragment.FaceNormal,
				fragment.FragmentColor,
				*job.Mat,
				*job.Lights,
				pipelineConfiguration.depthCheckMode,
				pixelProfiler
			);
		}
	}

	RenderTriangleCallCount++;
}
