#include "RenderingEngine3D.h"
#include "Engine.h"
#include "Primitive3DRenderer.h"

using namespace softengine;

RenderingEngine3D::RenderingEngine3D(
	std::shared_ptr<Scene3D> scene,
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
	camera(
		pixelsWidth,
		pixelsHeight,
		90.0,
		0.001,
		10000.0
	),
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
	RenderScene3D();
	surface->RenderPixels();
	textOverlay.RenderToSurface(*surface);
}

void RenderingEngine3D::RenderScene3D()
{
	for (Mesh3D& mesh : scene->Meshes())
	{
		Primitive3DRenderer::RenderMesh(
			*surface,
			mesh,
			camera
		);
	}
}
