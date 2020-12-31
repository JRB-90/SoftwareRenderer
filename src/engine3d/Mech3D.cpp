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
	drawType(mesh.drawType),
	material(mesh.material)
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
	Frame3D& transform)
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
	Material& material)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	material(material),
	drawType(DrawType::Triangles)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices,
	std::vector<Vertex3D> vertices,
	Frame3D& transform,
	DrawType drawType) 
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(drawType)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	DrawType drawType, 
	Material& material)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	drawType(drawType),
	material(material)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	Frame3D& transform, 
	Material& material)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	material(material),
	drawType(DrawType::Triangles)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	Frame3D& transform, 
	DrawType drawType, 
	Material& material)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(drawType),
	material(material)
{
}
