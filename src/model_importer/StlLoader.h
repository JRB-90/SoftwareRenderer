#pragma once

#include <string>

namespace softengine
{
	class Mesh3D;
	class Material;

	class StlLoader
	{
	public:
		StlLoader() = delete;

		static Mesh3D LoadMesh(
			const std::string& path,
			Material& material,
			bool flipVertexOrder = false,
			bool flipNormals = false
		);
	};
}