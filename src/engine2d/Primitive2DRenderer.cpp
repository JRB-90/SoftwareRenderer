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
		point.Vertex().Position,
		point.Transform()
	);
	surface.SetPixelValue(
		(int)p.X(),
		(int)p.Y(),
		point.Vertex().VertColor
	);
}

void Primitive2DRenderer::RenderLine(
	RenderSurface& surface, 
	Line2D& line)
{
	Vector2D p1 = MathUtils::TransformPointFor2D(
		line.V1().Position,
		line.Transform()
	);

	Vector2D p2 = MathUtils::TransformPointFor2D(
		line.V2().Position,
		line.Transform()
	);

	int yMax, yMin;
	RenderLinePoints(
		surface,
		Vertex2D(
			p1,
			line.V1().UVCoord,
			line.V1().VertColor
		),
		Vertex2D(
			p2,
			line.V2().UVCoord,
			line.V2().VertColor
		),
		yMax,
		yMin
	);
}

void Primitive2DRenderer::RenderLinePoints(
	RenderSurface& surface,
	Vertex2D v1, 
	Vertex2D v2,
	int& yMax, 
	int& yMin)
{
	double x = v1.Position.X();
	double y = v1.Position.Y();
	yMax = yMin = y;
	double dx = v2.Position.X() - v1.Position.X();
	double dy = v2.Position.Y() - v1.Position.Y();
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
			v1.VertColor  // TODO - Interpolate between colors
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
	// TODO - Make this use vertices

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
	Polygon2D& polygon,
	bool isWireFrame)
{
	// TODO - Make all renderingmethods in this class work with Vertex2D rather than Point2D/Line2D

	if (isWireFrame)
	{
		RenderPolygonLines(
			surface,
			polygon
		);
	}
	else
	{
		RenderPolygonFilled(
			surface,
			polygon
		);
	}
}

void Primitive2DRenderer::RenderPolygonLines(
	RenderSurface& surface, 
	Polygon2D& polygon)
{
	for (size_t i = 0; i < polygon.VBO().IndicesSize(); i += 3)
	{
		Line2D l1(
			polygon.VBO().Vertices(i),
			polygon.VBO().Vertices(i + 1),
			polygon.Transform()
		);

		Line2D l2(
			polygon.VBO().Vertices(i + 1),
			polygon.VBO().Vertices(i + 2),
			polygon.Transform()
		);

		Line2D l3(
			polygon.VBO().Vertices(i + 2),
			polygon.VBO().Vertices(i),
			polygon.Transform()
		);

		RenderLine(surface, l1);
		RenderLine(surface, l2);
		RenderLine(surface, l3);
	}
}

void Primitive2DRenderer::RenderPolygonFilled(
	RenderSurface& surface,
	Polygon2D& polygon)
{
	// TODO

	//if (!polygon.IsValid())
	//{
	//	std::cerr << "Attempted to render invlaid polygon" << std::endl;

	//	return;
	//}

	//std::vector<Vector2D> transformedPoints;
	//for (size_t i = 0; i < polygon.Points().size(); i++)
	//{
	//	transformedPoints.push_back(
	//		MathUtils::TransformPointFor2D(
	//			Vector2D(polygon.Points()[i]),
	//			polygon.Transform()
	//		)
	//	);
	//}

	//for (size_t i = 1; i < polygon.Points().size() - 1; i++)
	//{
	//	RenderTriangle(
	//		surface,
	//		Triangle2D(
	//			transformedPoints[0],
	//			transformedPoints[i],
	//			transformedPoints[i + 1],
	//			polygon.GetColor()
	//		)
	//	);
	//}
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
