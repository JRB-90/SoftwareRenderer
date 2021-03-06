#include "RenderingEngine3D.h"
#include "Engine.h"
#include "Scene3D.h"
#include "Camera.h"
#include "RenderSurface.h"
#include "RenderPipeline3D.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Profiler.h"

#include <iostream>

using namespace softengine;

RenderingEngine3D::RenderingEngine3D(
	std::shared_ptr<Scene3D> scene,
	std::shared_ptr<Camera> camera,
	size_t pixelsWidth,
	size_t pixelsHeight)
  :
	scene(std::move(scene)),
	pixelsWidth(pixelsWidth),
	pixelsHeight(pixelsHeight),
	pixelCount(pixelsWidth* pixelsHeight),
	screenBufSize(pixelCount * 4),
	refreshColor(Color::Black),
	textOverlay(
		14,
		Color::White
	),
	camera(std::move(camera)),
	isInitialised(false)
{
	pipeline = std::make_unique<RenderPipeline3D>(
		PipelineConfiguration(
			false,
			BackFaceCullingMode::Clockwise,
			DepthCheckMode::DepthCheckLessThan
		)
	);
}

RenderingEngine3D::RenderingEngine3D(
	std::shared_ptr<Scene3D> scene,
	std::shared_ptr<Camera> camera,
	size_t pixelsWidth,
	size_t pixelsHeight,
	PipelineConfiguration pipelineConfiguration)
  :
	scene(std::move(scene)),
	pixelsWidth(pixelsWidth),
	pixelsHeight(pixelsHeight),
	pixelCount(pixelsWidth* pixelsHeight),
	screenBufSize(pixelCount * 4),
	refreshColor(Color::Black),
	textOverlay(
		14,
		Color::White
	),
	camera(std::move(camera)),
	isInitialised(false)
{
}

RenderingEngine3D::~RenderingEngine3D()
{
}

void RenderingEngine3D::InitialiseToWindow(
	RenderingWindow& window, 
	RenderingMode renderingMode)
{
	surface = std::make_unique<RenderSurface>(
		pixelsWidth,
		pixelsHeight,
		window,
		renderingMode
	);

	isInitialised = true;
}

void RenderingEngine3D::WindowResized(RenderingWindow& window)
{
	surface->Resize(window);
	pixelsWidth = surface->Width();
	pixelsHeight = surface->Height();
	pixelCount = surface->PixelCount();
	screenBufSize = surface->ScreenBufSize();
	camera->Width(pixelsWidth);
	camera->Height(pixelsHeight);
}

void RenderingEngine3D::Render()
{
	if (!isInitialised)
	{
		return;
	}

	Profiler profiler;
	
	surface->FillWithColor(refreshColor);
	profiler.AddTiming("Refresh Screen");
	
	surface->ResetZBuffer();
	profiler.AddTiming("Reset Z Buffer");

	for (Mesh3D& mesh : scene->Meshes())
	{
		pipeline->Run(
			*surface,
			mesh.GetDrawType(),
			mesh.VBO(),
			mesh.Transform().Matrix(),
			*camera,
			mesh.GetMaterial(),
			scene->Lighting()
		);
	}

	profiler.AddTiming("Pipeline Total");

	surface->RenderPixels();
	profiler.AddTiming("Swap Chain");

	textOverlay.RenderToSurface(*surface);
	profiler.AddTiming("Text Overlay");

	profiler.PrintTimings();
}
