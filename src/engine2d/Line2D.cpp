#include "Line2D.h"
#include <cmath>

using namespace softengine;

Line2D::Line2D(const Line2D& line)
  :
	p1(line.p1),
	p2(line.p2),
	transform(line.transform),
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

bool Line2D::DoIntersect(
	const Line2D& l1,
	const Line2D& l2)
{
	double x1 = l1.p1.X();
    double x2 = l1.p2.X();
	double x3 = l2.p1.X();
	double x4 = l2.p2.X();

	double y1 = l1.p1.Y();
	double y2 = l1.p2.Y();
	double y3 = l2.p1.Y();
	double y4 = l2.p2.Y();

	// Check mutual abcisses
	if (std::fmax(x1, x2) < std::fmin(x3, x4))
	{
		return false;
	}

	double a1 = (y1 - y2) / (x1 - x2);
	double a2 = (y3 - y4) / (x3 - x4);
	double b1 = y1 - (a1 * x1);
	double b2 = y3 - (a2 * x3);

	// Check if parallel
	if (a1 == a2)
	{
		return false;
	}

	double xa = (b2 - b1) / (a1 - a2);

	if (xa < std::fmax(std::fmin(x1, x2), std::fmin(x3, x4)) ||
		xa > std::fmin(std::fmax(x1, x2), std::fmax(x3, x4)))
	{
		return false;
	}
	else
	{
		return true;
	}
}
