#pragma once

#include "Vertex2D.h"
#include <vector>

namespace softengine
{
	class VBO2D
	{
	public:
		VBO2D(const VBO2D& vbo);
		VBO2D(
			size_t indicesSize,
			size_t verticesSize
		);
		VBO2D(
			std::vector<size_t> indices,
			std::vector<Vertex2D> vertices
		);
		~VBO2D();

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
		Vertex2D& Vertices(size_t index);
		void Vertices(
			size_t index,
			Vertex2D& value
		);

	private:
		size_t indicesSize;
		size_t verticesSize;
		size_t* indices;
		Vertex2D* vertices;
	};
}