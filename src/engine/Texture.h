#pragma once

#include "IResource.h"
#include "Color.h"
#include "SDL.h"
#include <memory>

namespace softengine
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		Texture(const Texture& texture);
		Texture(
			size_t width,
			size_t height,
			Uint8* pixels
		);

		size_t Width() { return width; }
		size_t Height() { return height; }
		Color GetPixel(
			size_t x,
			size_t y
		);

	private:
		Uint8* pixels;
		size_t width;
		size_t height;
	};
}