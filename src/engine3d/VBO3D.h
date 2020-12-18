#pragma once

#include "Vertex3D.h"
#include <vector>

namespace softengine
{
	class VBO3D
	{
	public:
		VBO3D(const VBO3D& vbo);
		VBO3D(
			size_t indicesSize,
			size_t verticesSize
		);
		VBO3D(
			std::vector<size_t> indices,
			std::vector<Vertex3D> vertices
		);
		~VBO3D();

		void Clear();
		void Resize(
			size_t indicesSize,
			size_t verticesSize
		);

		size_t IndicesSize() { return indicesSize; }
		size_t VerticesSize() { return verticesSize; }
		size_t Indices(size_t index);
		void Indices(
			size_t index,
			size_t value
		);
		Vertex3D& Vertices(size_t index);
		void Vertices(
			size_t index,
			Vertex3D& value
		);

	private:
		size_t indicesSize;
		size_t verticesSize;
		size_t* indices;
		Vertex3D* vertices;
	};
}