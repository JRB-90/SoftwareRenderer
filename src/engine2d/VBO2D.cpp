#include "VBO2D.h"

#include <exception>

using namespace softengine;

VBO2D::VBO2D(const VBO2D& vbo)
  :
	indicesSize(vbo.indicesSize),
	verticesSize(vbo.verticesSize)
{
	indices = new size_t[indicesSize];
	vertices = new Vertex2D[verticesSize];

	for (size_t i = 0; i < indicesSize; i++)
	{
		indices[i] = vbo.indices[i];
	}

	for (size_t v = 0; v < verticesSize; v++)
	{
		vertices[v] = vbo.vertices[v];
	}
}

VBO2D::VBO2D(
	size_t indicesSize,
	size_t verticesSize)
  :
	indicesSize(indicesSize),
	verticesSize(verticesSize)
{
	indices = new size_t[indicesSize];
	vertices = new Vertex2D[verticesSize];
}

VBO2D::VBO2D(
	std::vector<size_t> indices,
	std::vector<Vertex2D> vertices)
  :
	indicesSize(indices.size()),
	verticesSize(vertices.size())
{
	this->indices = new size_t[indicesSize];
	this->vertices = new Vertex2D[verticesSize];

	for (size_t i = 0; i < indicesSize; i++)
	{
		this->indices[i] = indices[i];
	}

	for (size_t v = 0; v < verticesSize; v++)
	{
		this->vertices[v] = vertices[v];
	}
}

VBO2D::~VBO2D()
{
	if (indices != NULL)
	{
		delete[] indices;
	}
	if (vertices != NULL)
	{
		delete[] vertices;
	}
}

void VBO2D::Clear()
{
	indicesSize = 0;
	verticesSize = 0;
	delete[] indices;
	delete[] vertices;
	indices = NULL;
	vertices = NULL;
}

void VBO2D::Resize(
	size_t indicesSize, 
	size_t verticesSize)
{
	Clear();
	this->indicesSize = indicesSize;
	this->verticesSize = verticesSize;
	indices = new size_t[indicesSize];
	vertices = new Vertex2D[verticesSize];
}

size_t VBO2D::Indices(size_t index)
{
	if (index >= indicesSize)
	{
		throw std::exception("Indices index out of range");
	}

	return indices[index];
}

void VBO2D::Indices(
	size_t index,
	size_t value)
{
	if (index >= indicesSize)
	{
		throw std::exception("Indices index out of range");
	}

	indices[index] = value;
}

Vertex2D& VBO2D::Vertices(size_t index)
{
	if (index >= verticesSize)
	{
		throw std::exception("Vertices index out of range");
	}

	auto var1 = vertices[index];
	auto var2 = *(vertices + index);

	return vertices[index];
}

void VBO2D::Vertices(
	size_t index, 
	Vertex2D& value)
{
	if (index >= verticesSize)
	{
		throw std::exception("Vertices index out of range");
	}

	vertices[index] = value;
}
