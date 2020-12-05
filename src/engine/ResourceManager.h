#pragma once

#include "ImageLoader.h"
#include "Texture.h"
#include "IResource.h"
#include <vector>

namespace softengine
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		bool LoadImageResource(
			const std::string& name,
			Texture& texture
		);

	private:
		std::vector<IResource*> resources;
		ImageLoader imageLoader;
	};
}