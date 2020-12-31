#pragma once

#include <string>

namespace softengine
{
	class Mesh3D;

	class ModelImporter
	{
	public:
		ModelImporter() = delete;

		static Mesh3D LoadModel(
			const std::string& path,
			bool flipVertexOrder = false,
			bool flipNormals = false
		);
		static Mesh3D LoadModelResource(
			const std::string& name,
			bool flipVertexOrder = false,
			bool flipNormals = false
		);
	};
}