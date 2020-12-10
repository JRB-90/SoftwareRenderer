#pragma once

#include "SDL.h"

#include "SDL_ttf.h"
#include "Texture.h"

#include <string>

namespace softengine
{
	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();

		Texture LoadImageResource(const std::string& name);
		TTF_Font* LoadFontResource(
			const std::string& name,
			int fontSize
		);
	};
}