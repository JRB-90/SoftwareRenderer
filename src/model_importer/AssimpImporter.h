#pragma once

#include <string>

namespace softengine
{
	class Material;
	class Mesh3D;

	class AssimpImporter
	{
	public:
		AssimpImporter() = delete;

		static Mesh3D LoadMesh(
			const std::string& path,
			Material& material,
			bool flipVertexOrder = false,
			bool flipNormals = false
		);
	};
}