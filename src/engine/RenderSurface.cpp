#include "RenderSurface.h"

#include "Engine.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include <cmath>

using namespace softengine;

RenderSurface::RenderSurface(
	size_t pixelsWidth,
	size_t pixelsHeight,
	RenderingWindow& window,
	RenderingMode renderingMode)
  :
	pixelsWidth(pixelsWidth),
	pixelsHeight(pixelsHeight),
	pixelCount(pixelsWidth* pixelsHeight),
	screenBufSize(pixelCount * 4),
	renderer(NULL),
	texture(NULL),
	pixels(NULL)
{
	renderer =
		SDL_CreateRenderer(
			window.WindowHandle(),
			-1,
			Engine::ToSDLRenderingFlag(renderingMode)
		);

	texture =
		SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			pixelsWidth,
			pixelsHeight
		);

	pixels = new Uint8[screenBufSize];
	zBuffer = new double[pixelCount];
	ResetZBuffer();
}

RenderSurface::~RenderSurface()
{
	delete[] pixels;
	delete[] zBuffer;
	pixels = NULL;
	zBuffer = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
}

void RenderSurface::Resize(
	size_t windowWidth, 
	size_t windowHeight)
{
	// TODO - Handle window resize
	//	      Potentially try to maintain aspect ratio with pixels?
	//pixelsWidth = windowWidth;
	//pixelsHeight = windowHeight;
	//pixelCount = pixelsWidth * pixelsHeight;
	//screenBufSize = pixelCount * 4;
}

Color RenderSurface::GetPixelValue(int pixel) const
{
	if (pixel < 0 ||
		pixel >= pixelCount)
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}

	const size_t offset = 4 * pixel;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

Color RenderSurface::GetPixelValue(
	int pixelX,
	int pixelY) const
{
	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}

	const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

void RenderSurface::SetPixelValue(
	int pixel,
	Color& color)
{
	if (pixel < 0 ||
		pixel >= pixelCount)
	{
		return;
	}

	const size_t offset = 4 * pixel;
	pixels[offset + 0] = color.GetAs4B().b;
	pixels[offset + 1] = color.GetAs4B().g;
	pixels[offset + 2] = color.GetAs4B().r;
	pixels[offset + 3] = color.GetAs4B().a;
}

void RenderSurface::SetPixelValue(
	int pixelX,
	int pixelY,
	Color& color)
{

	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return;
	}

	const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;
	pixels[offset + 0] = color.GetAs4B().b;
	pixels[offset + 1] = color.GetAs4B().g;
	pixels[offset + 2] = color.GetAs4B().r;
	pixels[offset + 3] = color.GetAs4B().a;
}

double RenderSurface::GetZBufferVal(
	int pixelX,
	int pixelY)
{
	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return NAN;
	}
	else
	{
		return zBuffer[(pixelsWidth * pixelY) + pixelX];
	}
}

void RenderSurface::SetZBufferVal(
	int pixelX,
	int pixelY,
	double val)
{
	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return;
	}
	else
	{
		zBuffer[(pixelsWidth * pixelY) + pixelX] = val;
	}
}

SDL_Texture* RenderSurface::CreateSDLTexture(SDL_Surface* surface)
{
	return
		SDL_CreateTextureFromSurface(
			renderer,
			surface
		);
}

void RenderSurface::RenderTexture(
	SDL_Rect& position, 
	SDL_Texture* texture)
{
	SDL_RenderCopy(
		renderer,
		texture,
		NULL,
		&position
	);
	SDL_RenderPresent(renderer);
}

void RenderSurface::Clear(Color color)
{
	Color4B c = color.GetAs4B();
	SDL_SetRenderDrawColor(
		renderer,
		c.r,
		c.g,
		c.b,
		c.a
	);
	SDL_RenderClear(renderer);
}

void RenderSurface::FillWithColor(Color color)
{
	Color4B c = color.GetAs4B();
	for (size_t i = 0; i < screenBufSize; i += 4)
	{
		const size_t offset = i;
		pixels[i + 0] = c.b;
		pixels[i + 1] = c.g;
		pixels[i + 2] = c.r;
		pixels[i + 3] = c.a;
	}
}

void RenderSurface::ResetZBuffer()
{
	for (size_t i = 0; i < pixelCount; i++)
	{
		zBuffer[i] = FLT_MAX;
	}
}

void RenderSurface::RenderPixels()
{
	Uint8* lockedPixels = nullptr;
	int pitch = 0;
	SDL_LockTexture(
		texture,
		NULL,
		reinterpret_cast<void**>(&lockedPixels),
		&pitch
	);
	std::memcpy(
		lockedPixels,
		pixels,
		screenBufSize);
	SDL_UnlockTexture(texture);

	SDL_RenderCopy(
		renderer,
		texture,
		NULL,
		NULL
	);
	SDL_RenderPresent(renderer);
}
