#include "ResourceManager.h"

using namespace softengine;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (size_t i = 0; i < resources.size(); i++)
	{
		resources[i]->CleanupResource();
	}
}

bool ResourceManager::LoadImageResource(
	const std::string& name,
	Texture& texture)
{
	if (imageLoader.LoadImageResource(name, texture))
	{
		// TODO - Need to find a way to store the reference of the texture
		//		  object in the vector
		//resources.push_back(texture);

		return true;
	}
	else
	{
		return false;
	}
}
