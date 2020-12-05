#include "ImageLoader.h"

using namespace softengine;

ImageLoader::ImageLoader()
{
	IMG_Init(IMG_INIT_PNG);
}

bool ImageLoader::LoadImageResource(
	const std::string& name,
	Texture& texture)
{
	std::string path = "..\\..\\res\\" + name;
	SDL_Surface* image = IMG_Load(path.c_str());
	if (!image)
	{
		return false;
	}
	else
	{
		std::shared_ptr<SDL_Surface> surface =
			std::shared_ptr<SDL_Surface>(image);
		texture = Texture(surface);

		return true;
	}
}
