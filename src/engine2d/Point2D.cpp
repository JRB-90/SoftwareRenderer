#include "Point2D.h"

using namespace softengine;

Point2D::Point2D()
  :
	color(Color::White),
	size(1)
{
}

Point2D::Point2D(const Point2D& point)
  :
	position(point.position),
	color(point.color),
	size(point.size)
{
}

Point2D::Point2D(Vector2D position)
  :
	position(position),
	color(Color::White),
	size(1)
{
}

Point2D::Point2D(
	Vector2D position,
	Color color)
  :
	position(position),
	color(color),
	size(1)
{
}

Point2D::Point2D(
	Vector2D position, 
	uint16_t size)
  :
	position(position),
	color(Color::White),
	size(size)
{
}

Point2D::Point2D(
	Vector2D position, 
	Color color, 
	uint16_t size)
  :
	position(position),
	color(color),
	size(size)
{
}
