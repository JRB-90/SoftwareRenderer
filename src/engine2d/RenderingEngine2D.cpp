#include "RenderingEngine2D.h"
#include "Primitive2DRenderer.h"

#include <iostream>

using namespace softengine;

RenderingEngine2D::RenderingEngine2D(
	std::shared_ptr<Scene2D> scene, 
	size_t pixelsWidth, 
	size_t pixelsHeight)
  :
	scene(std::move(scene)),
	pixelsWidth(pixelsWidth),
	pixelsHeight(pixelsHeight),
	pixelCount(pixelsWidth * pixelsHeight),
	screenBufSize(pixelCount * 4),
	refreshColor(Color::Black),
	textOverlay(
		16,
		Color::White
	),
	isInitialised(false)
{
}

RenderingEngine2D::~RenderingEngine2D()
{
}

void RenderingEngine2D::InitialiseToWindow(
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

void RenderingEngine2D::WindowResized(
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

void RenderingEngine2D::Render()
{
	if (!isInitialised)
	{
		return;
	}

	surface->FillWithColor(refreshColor);
	RenderScene2D();
	surface->RenderPixels();
	textOverlay.RenderToSurface(*surface);
}

void RenderingEngine2D::RenderScene2D()
{
	for (Sprite2D& sprite : scene->Sprites())
	{
		Primitive2DRenderer::RenderSprite(
			*surface,
			sprite
		);
	}

	for (Polygon2D& polygon : scene->Polygons())
	{
		Primitive2DRenderer::RenderPolygon(
			*surface,
			polygon
		);
	}

	for (Line2D& line : scene->Lines())
	{
		Primitive2DRenderer::RenderLine(
			*surface,
			line
		);
	}

	for (Point2D& point : scene->Points())
	{
		Primitive2DRenderer::RenderPoint(
			*surface,
			point
		);
	}
}
