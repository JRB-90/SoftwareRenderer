#pragma once

#include <string>

namespace softengine
{
	class Mesh3D;

	class StlLoader
	{
	public:
		StlLoader() = delete;

		static Mesh3D LoadMesh(
			const std::string& path,
			bool flipVertexOrder = false,
			bool flipNormals = false
		);
	};
}