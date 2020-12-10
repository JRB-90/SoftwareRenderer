#include "ResourceLoader.h"
#include "SDL_image.h"

#include <stdexcept>

#include <filesystem>

using namespace softengine;

ResourceLoader::ResourceLoader()
{
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
}

ResourceLoader::~ResourceLoader()
{
	IMG_Quit();
	TTF_Quit();
}

Texture ResourceLoader::LoadImageResource(const std::string& name)
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

TTF_Font* ResourceLoader::LoadFontResource(
	const std::string& name,
	int fontSize)
{
	std::string path = "..\\..\\res\\fonts\\" + name;
	TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
	auto error = TTF_GetError();
	if (!font)
	{
		throw std::runtime_error("Failed to load font");
	}
	else
	{
		return font;
	}
}
