#include "Triangle2D.h"

using namespace softengine;

Triangle2D::Triangle2D(const Triangle2D& triangle)
  :
	p1(triangle.p1),
	p2(triangle.p2),
	p3(triangle.p3),
	color(triangle.color)
{
}

Triangle2D::Triangle2D(
	Vector2D p1,
	Vector2D p2,
	Vector2D p3)
  :
	p1(p1),
	p2(p2),
	p3(p3),
	color(Color::White)
{
}

Triangle2D::Triangle2D(
	Vector2D p1,
	Vector2D p2,
	Vector2D p3,
	Color color)
  :
	p1(p1),
	p2(p2),
	p3(p3),
	color(color)
{
}