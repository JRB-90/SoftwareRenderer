#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"

#include <string>

namespace softengine
{
	class ImageLoader
	{
	public:
		ImageLoader();

		Texture ImageLoader::LoadImageResource(const std::string& name);
	};
}