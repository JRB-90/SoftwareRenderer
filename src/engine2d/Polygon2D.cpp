#include "Polygon2D.h"

using namespace softengine;

Polygon2D::Polygon2D()
  :
	vbo(
		VBO2D(0, 0)
	),
	drawType(DrawType::Points)
{
}

Polygon2D::Polygon2D(const Polygon2D& polygon)
  :
	vbo(polygon.vbo),
	transform(polygon.transform),
	drawType(polygon.drawType)
{
}

Polygon2D::Polygon2D(
	std::vector<size_t> indices,
	std::vector<Vertex2D> vertices)
  :
	vbo(
		VBO2D(
			indices,
			vertices
		)
	),
	drawType(DrawType::Points)
{
}

Polygon2D::Polygon2D(
	std::vector<size_t> indices, 
	std::vector<Vertex2D> vertices, 
	DrawType drawType)
  :
	vbo(
		VBO2D(
			indices,
			vertices
		)
	),
	drawType(drawType)
{
}

Polygon2D::Polygon2D(
	std::vector<size_t> indices, 
	std::vector<Vertex2D> vertices, 
	Frame2D transform)
  :
	vbo(
		VBO2D(
			indices,
			vertices
		)
	),
	transform(transform),
	drawType(DrawType::Points)
{
}

Polygon2D::Polygon2D(
	std::vector<size_t> indices, 
	std::vector<Vertex2D> vertices, 
	DrawType drawType,
	Frame2D transform)
  :
	vbo(
		VBO2D(
			indices,
			vertices
		)
	),
	drawType(drawType),
	transform(transform)
{
}
