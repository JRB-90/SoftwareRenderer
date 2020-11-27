#include "Line2D.h"

using namespace softengine;

Line2D::Line2D(const Line2D& line)
  :
	p1(line.p1),
	p2(line.p2),
	color(line.color),
	width(line.width)
{
}

Line2D::Line2D(
	Vector2D p1, 
	Vector2D p2)
  :
	p1(p1),
	p2(p2),
	color(Color::White),
	width(1)
{
}

Line2D::Line2D(
	Vector2D p1, 
	Vector2D p2, 
	Color color)
  :
	p1(p1),
	p2(p2),
	color(color),
	width(1)
{
}

Line2D::Line2D(
	Vector2D p1, 
	Vector2D p2, 
	uint16_t width)
  :
	p1(p1),
	p2(p2),
	color(Color::White),
	width(width)
{
}

Line2D::Line2D(
	Vector2D p1, 
	Vector2D p2, 
	Color color, 
	uint16_t width)
  :
	p1(p1),
	p2(p2),
	color(color),
	width(width)
{
}
