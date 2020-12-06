#include "Texture.h"
#include <cinttypes>

using namespace softengine;

Texture::Texture()
  :
	pixels(NULL),
	width(0),
	height(0)
{
}

Texture::~Texture()
{
	if (pixels != NULL)
	{
		delete[] pixels;
		pixels = NULL;
	}
}

Texture::Texture(const Texture& texture)
  :
	width(texture.width),
	height(texture.height)
{
	size_t size = width * height * 4;
	pixels = new Uint8[size];
	std::memcpy(this->pixels, texture.pixels, size);
}

Texture::Texture(
	size_t width,
	size_t height,
	Uint8* pixels)
  :
	width(width),
	height(height)
{
	size_t size = width * height * 4;
	this->pixels = new Uint8[size];
	std::memcpy(this->pixels, pixels, size);
}

Color Texture::GetPixel(
	size_t x, 
	size_t y)
{
	if (x >= 0 &&
		x < width &&
		y >= 0 &&
		y < height)
	{
		size_t off = (y * 4 * width) + (x * 4);

		return Color(
			pixels[off + 0],
			pixels[off + 1],
			pixels[off + 2],
			pixels[off + 3]
		);
	}
	else
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}
}
