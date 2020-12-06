#include "ImageLoader.h"
#include <stdexcept>

using namespace softengine;

ImageLoader::ImageLoader()
{
	IMG_Init(IMG_INIT_PNG);
}

Texture ImageLoader::LoadImageResource(const std::string& name)
{
	std::string path = "..\\..\\res\\" + name;
	SDL_Surface* image = IMG_Load(path.c_str());
	if (!image)
	{
		throw std::runtime_error("Failed to load texture");
	}
	else
	{
		size_t totalSize = image->w * image->h * image->format->BytesPerPixel;
		Uint8* pixels = new Uint8[image->w * image->h * 4];
		Uint8* p = (Uint8*)image->pixels;
		Uint8 r, g, b, a;

		for (size_t i = 0; i < totalSize; i++)
		{
			SDL_GetRGBA(
				p[i],
				image->format,
				&r,
				&g,
				&b,
				&a
			);

			pixels[(i * 4) + 0] = r;
			pixels[(i * 4) + 1] = g;
			pixels[(i * 4) + 2] = b;
			pixels[(i * 4) + 3] = a;
		}

		Texture texture = Texture(
			image->w,
			image->h,
			pixels
		);

		delete[] pixels;
		pixels = NULL;
		SDL_FreeSurface(image);

		return texture;
	}
}
