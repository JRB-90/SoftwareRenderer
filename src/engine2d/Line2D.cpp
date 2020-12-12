#include "Line2D.h"
#include <cmath>

using namespace softengine;

Line2D::Line2D(const Line2D& line)
  :
	v1(line.v1),
	v2(line.v2),
	transform(line.transform),
	width(line.width)
{
}

Line2D::Line2D(
	Vertex2D v1, 
	Vertex2D v2)
  :
	v1(v1),
	v2(v2),
	width(1.0)
{
}

Line2D::Line2D(
	Vertex2D v1, 
	Vertex2D v2, 
	Frame2D transform)
  :
	v1(v1),
	v2(v2),
	transform(transform),
	width(1.0)
{
}

Line2D::Line2D(
	Vertex2D v1, 
	Vertex2D v2, 
	uint16_t width)
  :
	v1(v1),
	v2(v2),
	width(width)
{
}

Line2D::Line2D(
	Vertex2D v1, 
	Vertex2D v2, 
	Frame2D transform, 
	uint16_t width)
  :
	v1(v1),
	v2(v2),
	transform(transform),
	width(width)
{
}



bool Line2D::DoIntersect(
	const Line2D& l1,
	const Line2D& l2)
{
	double x1 = l1.v1.Position.X();
    double x2 = l1.v2.Position.X();
	double x3 = l2.v1.Position.X();
	double x4 = l2.v2.Position.X();

	double y1 = l1.v1.Position.Y();
	double y2 = l1.v2.Position.Y();
	double y3 = l2.v1.Position.Y();
	double y4 = l2.v2.Position.Y();

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
