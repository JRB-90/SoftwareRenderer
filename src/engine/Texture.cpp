#include "Texture.h"
#include <cinttypes>

using namespace softengine;

Texture::Texture()
{
}

Texture::~Texture()
{
}

Texture::Texture(const Texture& texture)
{
	this->surface = std::move(texture.surface);
}

Texture::Texture(std::shared_ptr<SDL_Surface> surface)
  :
	surface(std::move(surface))
{
}

void Texture::CleanupResource()
{

}

size_t softengine::Texture::Width()
{
	if (surface.get() != nullptr)
	{
		return surface->w;
	}
	else
	{
		return 0;
	}
}

size_t softengine::Texture::Height()
{
	if (surface.get() != nullptr)
	{
		return surface->h;
	}
	else
	{
		return 0;
	}
}

Color softengine::Texture::GetPixel(
	size_t x, 
	size_t y)
{
	if (surface.get() != nullptr)
	{
		Uint8 bpp = surface->format->BytesPerPixel;
		Uint8* p = (Uint8*)surface->pixels;
		size_t off = (y * surface->w) + x;
		uint8_t r, g, b, a;

		SDL_GetRGBA(
			p[off],
			surface->format,
			&r,
			&g,
			&b,
			&a
		);

		return Color(r, g, b, a);
	}
	else
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}
}
