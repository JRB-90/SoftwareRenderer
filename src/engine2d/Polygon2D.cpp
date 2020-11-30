#include "Polygon2D.h"

using namespace softengine;

Polygon2D::Polygon2D()
  :
	color(Color::White)
{
}

Polygon2D::Polygon2D(Color color)
  :
	color(color)
{
}

Polygon2D::Polygon2D(std::vector<Vector2D> points)
  :
	points(points),
	color(Color::White)
{
}

Polygon2D::Polygon2D(
	std::vector<Vector2D> points,
	Color color)
  :
	points(points),
	color(color)
{
}

void Polygon2D::ClearPoints()
{
	points.clear();
}

void Polygon2D::AddPoint(Vector2D& point)
{
	points.push_back(point);
}
