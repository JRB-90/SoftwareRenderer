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
	renderer(NULL),
	texture(NULL),
	pixels(NULL),
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
	if (!isInitialised)
	{
		delete[] pixels;
		pixels = NULL;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
	}
}

void RenderingEngine3D::InitialiseToWindow(
	RenderingWindow& window, 
	RenderingMode renderingMode)
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
	isInitialised = true;
}

void RenderingEngine3D::WindowResized(
	size_t windowWidth, 
	size_t windowHeight)
{
	// TODO - Handle window resize
	//	      Potentially try to maintain aspect ratio with pixels?
}

void RenderingEngine3D::Render()
{
	if (!isInitialised)
	{
		return;
	}

	for (size_t j = 0; j < pixelsHeight; j++)
	{
		for (size_t i = 0; i < pixelsWidth; i++)
		{
			const size_t offset = (pixelsWidth * 4 * j) + (i * 4);
			pixels[offset + 0] = refreshColor.GetAs4B().b;
			pixels[offset + 1] = refreshColor.GetAs4B().g;
			pixels[offset + 2] = refreshColor.GetAs4B().r;
			pixels[offset + 3] = refreshColor.GetAs4B().a;
		}
	}

	//RenderScene3D();

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

Color RenderingEngine3D::GetPixelValue(size_t pixel) const
{
	const size_t offset = 4 * pixel;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

Color RenderingEngine3D::GetPixelValue(
	size_t pixelX, 
	size_t pixelY) const
{
	const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

void RenderingEngine3D::SetPixelValue(
	size_t pixel, 
	Color& color)
{
	const size_t offset = 4 * pixel;
	pixels[offset + 0] = color.GetAs4B().b;
	pixels[offset + 1] = color.GetAs4B().g;
	pixels[offset + 2] = color.GetAs4B().r;
	pixels[offset + 3] = color.GetAs4B().a;
}

void RenderingEngine3D::SetPixelValue(
	size_t pixelX, 
	size_t pixelY, 
	Color& color)
{
	if (pixelX > 0 &&
		pixelX < pixelsWidth &&
		pixelY > 0 &&
		pixelY < pixelsHeight)
	{
		const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;
		pixels[offset + 0] = color.GetAs4B().b;
		pixels[offset + 1] = color.GetAs4B().g;
		pixels[offset + 2] = color.GetAs4B().r;
		pixels[offset + 3] = color.GetAs4B().a;
	}
}

void RenderingEngine3D::RenderScene3D()
{
	// TODO
}
