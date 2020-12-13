#include "Point2D.h"

using namespace softengine;

Point2D::Point2D()
  :
	size(1)
{
}

Point2D::Point2D(const Point2D& point)
  :
	vertex(point.vertex),
	transform(point.transform),
	size(point.size)
{
}

Point2D::Point2D(Vertex2D vertex)
  :
	vertex(vertex),
	size(1)
{
}

Point2D::Point2D(
	Vertex2D vertex, 
	Frame2D transform)
  :
	vertex(vertex),
	transform(transform),
	size(1)
{
}

Point2D::Point2D(
	Vertex2D position, 
	uint16_t size)
  :
	vertex(vertex),
	size(size)
{
}

Point2D::Point2D(
	Vertex2D vertex, 
	Frame2D transform,
	uint16_t size)
  :
	vertex(vertex),
	transform(transform),
	size(size)
{
}
