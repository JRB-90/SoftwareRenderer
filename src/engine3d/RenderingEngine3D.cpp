#include "RenderingEngine3D.h"
#include "Engine.h"

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
	refreshColor(
		Color(
			0.0,
			0.0,
			0.0,
			1.0
		)
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
	RenderScene3D();
	textOverlay.RenderToSurface(*surface);
	surface->Render();
}

void RenderingEngine3D::RenderScene3D()
{
	// TODO
}
