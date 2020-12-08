#include "Primitive2DRenderer.h"

#include "MathUtils.h"
#include "Utils2D.h"
#include <iostream>

using namespace softengine;

void Primitive2DRenderer::RenderPoint(
	RenderSurface& surface,
	Point2D& point)
{
	Vector2D p = MathUtils::TransformPointFor2D(
		point.Position(),
		point.Transform()
	);
	surface.SetPixelValue(
		(size_t)p.X(),
		(size_t)p.Y(),
		point.GetColor()
	);
}

void Primitive2DRenderer::RenderLine(
	RenderSurface& surface, 
	Line2D& line)
{
	Vector2D p1 = MathUtils::TransformPointFor2D(
		line.P1(),
		line.Transform()
	);

	Vector2D p2 = MathUtils::TransformPointFor2D(
		line.P2(),
		line.Transform()
	);

	int yMax, yMin;
	RenderLinePoints(
		surface,
		p1,
		p2,
		line.GetColor(),
		yMax,
		yMin
	);
}

void Primitive2DRenderer::RenderLinePoints(
	RenderSurface& surface,
	Vector2D p1, 
	Vector2D p2, 
	Color color, 
	int& yMax, 
	int& yMin)
{
	double x = p1.X();
	double y = p1.Y();
	yMax = yMin = y;
	double dx = p2.X() - p1.X();
	double dy = p2.Y() - p1.Y();
	int steps;

	if (std::abs(dx) > std::abs(dy))
	{
		steps = (int)std::abs(dx);
	}
	else
	{
		steps = (int)std::abs(dy);
	}

	double xInc = dx / (double)steps;
	double yInc = dy / (double)steps;

	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yInc;
		surface.SetPixelValue(
			x,
			y,
			color
		);

		if (y > yMax)
		{
			yMax = y;
		}
		if (y < yMin)
		{
			yMin = y;
		}
	}
}

void Primitive2DRenderer::RenderTriangle(
	RenderSurface& surface, 
	Triangle2D& triangle)
{
	Vector2D p0 = triangle.P1();
	Vector2D p1 = triangle.P2();
	Vector2D p2 = triangle.P3();

	if (p1.Y() < p0.Y())
	{
		Vector2D temp = p1;
		p1 = p0;
		p0 = temp;
	}
	if (p2.Y() < p0.Y())
	{
		Vector2D temp = p2;
		p2 = p0;
		p0 = temp;
	}
	if (p2.Y() < p1.Y())
	{
		Vector2D temp = p2;
		p2 = p1;
		p1 = temp;
	}

	std::vector<int> x01 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p1.X(),
			p1.Y()
		);

	std::vector<int> x12 =
		Utils2D::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p2.X(),
			p2.Y()
		);

	x01.pop_back();
	std::vector<int> x012;
	for (auto x : x01)
	{
		x012.push_back(x);
	}
	for (auto x : x12)
	{
		x012.push_back(x);
	}

	std::vector<int> xLeft;
	std::vector<int> xRight;
	int m = x02.size() / 2;
	if (x02[m] < x012[m])
	{
		xLeft = x02;
		xRight = x012;
	}
	else
	{
		xLeft = x012;
		xRight = x02;
	}

	for (int y = p0.Y(); y < p2.Y(); y++)
	{
		for (int x = xLeft[y - p0.Y()]; x < xRight[y - p0.Y()]; x++)
		{
			surface.SetPixelValue(
				x,
				y,
				triangle.GetColor()
			);
		}
	}
}

void Primitive2DRenderer::RenderPolygon(
	RenderSurface& surface, 
	Polygon2D& polygon)
{
	if (polygon.Points().size() == 0)
	{
		return;
	}
	else if (polygon.Points().size() == 1)
	{
		Vector2D p = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[0]),
			polygon.Transform()
		);
		RenderPoint(
			surface,
			Point2D(
				p,
				polygon.GetColor()
			)
		);
	}
	else if (polygon.Points().size() == 2)
	{
		Vector2D p1 = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[0]),
			polygon.Transform()
		);
		Vector2D p2 = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[1]),
			polygon.Transform()
		);

		RenderLine(
			surface,
			Line2D(
				p1,
				p2,
				polygon.GetColor()
			)
		);
	}
	else
	{
		RenderPolygonFilled(
			surface, 
			polygon
		);
		//RenderPolygonLines(
		//	surface,
		//	polygon
		//);
	}
}

void Primitive2DRenderer::RenderPolygonLines(
	RenderSurface& surface, 
	Polygon2D& polygon)
{
	std::vector<Vector2D> transformedPoints;
	for (size_t i = 0; i < polygon.Points().size(); i++)
	{
		transformedPoints.push_back(
			MathUtils::TransformPointFor2D(
				Vector2D(polygon.Points()[i]),
				polygon.Transform()
			)
		);
	}

	for (size_t i = 0; i < polygon.Points().size() - 1; i++)
	{
		RenderLine(
			surface,

			Line2D(
				transformedPoints[i],
				transformedPoints[i + 1],
				Color::White
			)
		);
	}
	RenderLine(
		surface,

		Line2D(
			transformedPoints[transformedPoints.size() - 1],
			transformedPoints[0],
			Color::White
		)
	);
}

void Primitive2DRenderer::RenderPolygonFilled(
	RenderSurface& surface,
	Polygon2D& polygon)
{
	if (!polygon.IsValid())
	{
		std::cerr << "Attempted to render invlaid polygon" << std::endl;

		return;
	}

	std::vector<Vector2D> transformedPoints;
	for (size_t i = 0; i < polygon.Points().size(); i++)
	{
		transformedPoints.push_back(
			MathUtils::TransformPointFor2D(
				Vector2D(polygon.Points()[i]),
				polygon.Transform()
			)
		);
	}

	for (size_t i = 1; i < polygon.Points().size() - 1; i++)
	{
		RenderTriangle(
			surface,
			Triangle2D(
				transformedPoints[0],
				transformedPoints[i],
				transformedPoints[i + 1],
				polygon.GetColor()
			)
		);
	}
}

void Primitive2DRenderer::RenderSprite(
	RenderSurface& surface, 
	Sprite2D& sprite)
{
	for (size_t i = 0; i < sprite.Width(); i++)
	{
		for (size_t j = 0; j < sprite.Height(); j++)
		{
			Color pc = sprite.GetPixel(
				i,
				j
			);
			if (IsValidSpritePixel(pc))
			{
				Vector2D pos = sprite.Transform().Position();
				surface.SetPixelValue(
					i + (int)pos.X(),
					j + (int)pos.Y(),
					pc
				);
			}
		}
	}
}

bool Primitive2DRenderer::IsValidSpritePixel(Color& color)
{
	Color4B c = color.GetAs4B();
	if (c.r == 140 &&
		c.g == 43 &&
		c.b == 150 &&
		c.a == 255)
	{
		return false;
	}
	else
	{
		return true;
	}
}
