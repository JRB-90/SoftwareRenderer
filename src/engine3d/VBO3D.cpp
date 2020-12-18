#include "VBO3D.h"

using namespace softengine;

VBO3D::VBO3D(const VBO3D& vbo)
  :
	indicesSize(vbo.indicesSize),
	verticesSize(vbo.verticesSize)
{
	indices = new size_t[indicesSize];
	vertices = new Vertex3D[verticesSize];

	for (size_t i = 0; i < indicesSize; i++)
	{
		indices[i] = vbo.indices[i];
	}

	for (size_t v = 0; v < verticesSize; v++)
	{
		vertices[v] = vbo.vertices[v];
	}
}

VBO3D::VBO3D(
	size_t indicesSize, 
	size_t verticesSize)
  :
	indicesSize(indicesSize),
	verticesSize(verticesSize)
{
	indices = new size_t[indicesSize];
	vertices = new Vertex3D[verticesSize];
}

VBO3D::VBO3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices)
  :
	indicesSize(indices.size()),
	verticesSize(vertices.size())
{
	this->indices = new size_t[indicesSize];
	this->vertices = new Vertex3D[verticesSize];

	for (size_t i = 0; i < indicesSize; i++)
	{
		this->indices[i] = indices[i];
	}

	for (size_t v = 0; v < verticesSize; v++)
	{
		this->vertices[v] = vertices[v];
	}
}

VBO3D::~VBO3D()
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

void VBO3D::Clear()
{
	indicesSize = 0;
	verticesSize = 0;
	delete[] indices;
	delete[] vertices;
	indices = NULL;
	vertices = NULL;
}

void VBO3D::Resize(
	size_t indicesSize, 
	size_t verticesSize)
{
	Clear();
	this->indicesSize = indicesSize;
	this->verticesSize = verticesSize;
	indices = new size_t[indicesSize];
	vertices = new Vertex3D[verticesSize];
}

size_t VBO3D::Indices(size_t index)
{
	if (index >= indicesSize)
	{
		throw std::exception("Indices index out of range");
	}

	return indices[index];
}

void VBO3D::Indices(
	size_t index, 
	size_t value)
{
	if (index >= indicesSize)
	{
		throw std::exception("Indices index out of range");
	}

	indices[index] = value;
}

Vertex3D& VBO3D::Vertices(size_t index)
{
	if (index >= verticesSize)
	{
		throw std::exception("Vertices index out of range");
	}

	auto var1 = vertices[index];
	auto var2 = *(vertices + index);

	return vertices[index];
}

void VBO3D::Vertices(
	size_t index, 
	Vertex3D& value)
{
	if (index >= verticesSize)
	{
		throw std::exception("Vertices index out of range");
	}

	vertices[index] = value;
}
