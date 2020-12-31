#include "ModelImporter.h"

#include "Mesh3D.h"
#include "StlLoader.h"
#include <iostream>
#include <filesystem>

using namespace softengine;

Mesh3D ModelImporter::LoadModel(
	const std::string& path,
	bool flipVertexOrder,
	bool flipNormals)
{
	std::filesystem::path p(path);
	if (!std::filesystem::exists(p))
	{
		throw std::runtime_error("Failed to load model file at: " + path);
	}
	if (!p.has_extension())
	{
		throw std::runtime_error("File does not have an extension");
	}

	std::string ext(p.extension().u8string());
	std::transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
	if (ext == ".STL")
	{
		return StlLoader::LoadMesh(
			p.u8string(),
			flipVertexOrder,
			flipNormals
		);
	}
	else
	{
		throw std::runtime_error("File type [" + ext + "] not supported");
	}
}

Mesh3D ModelImporter::LoadModelResource(
	const std::string& name,
	bool flipVertexOrder,
	bool flipNormals)
{
	std::string path = "..\\..\\res\\" + name;
	
	return LoadModel(path, flipVertexOrder, flipNormals);
}
