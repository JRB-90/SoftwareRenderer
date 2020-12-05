#pragma once

#include "IResource.h"
#include "Color.h"
#include "SDL.h"
#include <memory>

namespace softengine
{
	class Texture : public IResource
	{
	public:
		Texture();
		~Texture();
		Texture(const Texture& texture);
		Texture(std::shared_ptr<SDL_Surface> surface);

		virtual void CleanupResource() override;

		size_t Width();
		size_t Height();
		Color GetPixel(
			size_t x,
			size_t y
		);

	private:
		std::shared_ptr<SDL_Surface> surface;
	};
}