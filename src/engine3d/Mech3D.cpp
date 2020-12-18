#include "Mesh3D.h"

using namespace softengine;

Mesh3D::Mesh3D()
  :
	vbo(
		VBO3D(0, 0)
	),
	drawType(DrawType::Triangles)
{
}

Mesh3D::Mesh3D(const Mesh3D& mesh)
  :
	vbo(mesh.vbo),
	transform(mesh.transform),
	drawType(mesh.drawType)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	drawType(DrawType::Triangles)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	DrawType drawType)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	drawType(drawType)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	Frame3D transform)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(DrawType::Triangles)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices,
	std::vector<Vertex3D> vertices,
	DrawType drawType, 
	Frame3D transform)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	drawType(drawType),
	transform(transform)
{
}
