#include "RenderingEngine3D.h"
#include "Engine.h"
#include "Scene3D.h"
#include "Camera.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "RenderPipeline3D.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"

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
		false,
		DrawType::Points,
		BackFaceCullingMode::Clockwise,
		DepthCheckMode::DepthCheckGreaterThan
	);
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

void RenderingEngine3D::WindowResized(
	size_t windowWidth, 
	size_t windowHeight)
{
	surface->Resize(
		windowWidth,
		windowHeight
	);
	pixelsWidth = surface->Width();
	pixelsHeight = surface->Height();
	pixelCount = surface->PixelCount();
	screenBufSize = surface->ScreenBufSize();
}

void RenderingEngine3D::Render()
{
	if (!isInitialised)
	{
		return;
	}

	surface->FillWithColor(refreshColor);
	surface->ResetZBuffer();

	for (Mesh3D& mesh : scene->Meshes())
	{
		pipeline->SetDrawType(mesh.GetDrawType());
		pipeline->Run(
			*surface,
			mesh.VBO(),
			mesh.Transform().Matrix(),
			*camera,
			mesh.GetTextrue()
		);
	}

	surface->RenderPixels();
	textOverlay.RenderToSurface(*surface);
}
