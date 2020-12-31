#include "StlLoader.h"

#include "FileUtils.h"
#include "Material.h"
#include "ShadingType.h"
#include "Mesh3D.h"
#include "Vertex3D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Color.h"
#include <iostream>
#include <fstream>

using namespace softengine;

Mesh3D StlLoader::LoadMesh(
	const std::string& path,
	bool flipVertexOrder,
	bool flipNormals)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
	}

	std::vector<Vertex3D> vertices;
	Vector3D normal;

	std::string line;
	while (std::getline(file, line))
	{
		if (line == "")
		{
			continue;
		}
		
		std::vector<std::string> tokens = FileUtils::explode(line, ' ');
		if (tokens[0] == "solid")
		{
			// Parse out name at a later date
		}
		else if (tokens[0] == "facet")
		{
			double x = std::stod(tokens[2]);
			double y = std::stod(tokens[3]);
			double z = std::stod(tokens[4]);
			normal = Vector3D(x, y, z);
			if (flipNormals)
			{
				normal = normal * -1.0;
			}
		}
		else if (tokens[0] == "vertex")
		{
			double x = std::stod(tokens[1]);
			double y = std::stod(tokens[2]);
			double z = std::stod(tokens[3]);
			Vector3D position(x, y, z);
			vertices.push_back(
				Vertex3D(
					position,
					Vector2D(-1, -1),
					normal,
					Color(0.5, 0.5, 0.5, 1.0)
				)
			);
		}
	}

	std::vector<size_t> indices;
	for (size_t i = 0; i < vertices.size() - 2; i += 3)
	{
		if (flipVertexOrder)
		{
			indices.push_back(i + 2);
			indices.push_back(i + 1);
			indices.push_back(i);
		}
		else
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
	}

	return 
		Mesh3D(
			indices,
			vertices,
			Material(Color(Color::Red), ShadingType::Phong)
		);
}
