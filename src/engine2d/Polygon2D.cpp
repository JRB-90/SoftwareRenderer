#include "Polygon2D.h"
#include "Line2D.h"

using namespace softengine;

Polygon2D::Polygon2D()
  :
	color(Color::White),
	isValid(false)
{
}

Polygon2D::Polygon2D(const Polygon2D& polygon)
  :
	points(polygon.points),
	transform(polygon.transform),
	color(polygon.color),
	isValid(polygon.isValid)
{
}

Polygon2D::Polygon2D(Color color)
  :
	color(color),
	isValid(false)
{
}

Polygon2D::Polygon2D(std::vector<Vector2D> points)
  :
	points(points),
	color(Color::White)
{
	CheckIsValid();
}

Polygon2D::Polygon2D(
	std::vector<Vector2D> points,
	Color color)
  :
	points(points),
	color(color)
{
	CheckIsValid();
}

void Polygon2D::ClearPoints()
{
	points.clear();
	isValid = false;
}

void Polygon2D::AddPoint(Vector2D& point)
{
	points.push_back(point);
	CheckIsValid();
}

void Polygon2D::CheckIsValid()
{
	if (points.size() > 0 &&
		points.size() < 4)
	{
		isValid = true;

		return;
	}

	for (size_t i = 0; i < points.size() - 3; i++)
	{
		Line2D l1(
			points[i],
			points[i + 1]
		);
		for (size_t j = i + 1; j < points.size() - 2; j++)
		{
			Line2D l2(
				points[j + 1],
				points[j + 2]
			);

			if (Line2D::DoIntersect(l1, l2))
			{
				isValid = false;

				return;
			}
		}
	}

	isValid = true;
}
