#include "Mesh3D.h"

using namespace softengine;

Mesh3D::Mesh3D()
  :
	vbo(
		VBO3D(0, 0)
	),
	drawType(DrawType::Triangles),
	shadingType(ShadingType::Phong)
{
}

Mesh3D::Mesh3D(const Mesh3D& mesh)
  :
	vbo(mesh.vbo),
	transform(mesh.transform),
	texture(mesh.texture),
	drawType(mesh.drawType),
	shadingType(ShadingType::Phong)
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
	drawType(DrawType::Triangles),
	shadingType(ShadingType::Phong)
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
	drawType(drawType),
	shadingType(ShadingType::Phong)
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
	drawType(DrawType::Triangles),
	shadingType(ShadingType::Phong)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices,
	std::vector<Vertex3D> vertices,
	Frame3D transform,
	DrawType drawType) 
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(drawType),
	shadingType(ShadingType::Phong)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	Frame3D transform, 
	DrawType drawType, 
	ShadingType shadingType)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(drawType),
	shadingType(shadingType)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices,
	std::vector<Vertex3D> vertices,
	Frame3D transform,
	Texture texture)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	texture(texture),
	drawType(DrawType::Triangles),
	shadingType(ShadingType::Phong)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices,
	std::vector<Vertex3D> vertices,
	Frame3D transform,
	Texture texture,
	DrawType drawType)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	texture(texture),
	drawType(drawType),
	shadingType(ShadingType::Phong)
{
}

Mesh3D::Mesh3D(
	std::vector<size_t> indices, 
	std::vector<Vertex3D> vertices, 
	Frame3D transform, 
	Texture texture, 
	DrawType drawType, 
	ShadingType shadingType)
  :
	vbo(
		VBO3D(
			indices,
			vertices
		)
	),
	transform(transform),
	texture(texture),
	drawType(drawType),
	shadingType(shadingType)
{
}
