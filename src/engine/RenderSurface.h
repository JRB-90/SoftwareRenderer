#pragma once

#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Color.h"
#include "SDL.h"

namespace softengine
{
	class RenderSurface
	{
	public:
		RenderSurface(
			size_t pixelsWidth,
			size_t pixelsHeight,
			RenderingWindow& window,
			RenderingMode renderingMode
		);
		~RenderSurface();

		void Resize(
			size_t windowWidth,
			size_t windowHeight
		);
		Color GetPixelValue(int pixel) const;
		Color GetPixelValue(
			int pixelX,
			int pixelY) const;
		void SetPixelValue(
			int pixel,
			Color& color
		);
		void SetPixelValue(
			int pixelX,
			int pixelY,
			Color& color
		);
		void FillWithColor(Color color);
		void Render();

		size_t Width() const { return pixelsWidth; }
		size_t Height() const { return pixelsHeight; }
		size_t PixelCount() const { return pixelCount; }
		size_t ScreenBufSize() const { return screenBufSize; }

	private:
		size_t pixelsWidth;
		size_t pixelsHeight;
		size_t pixelCount;
		size_t screenBufSize;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint8* pixels;
	};
}