#include "Primitive2DRenderer.h"

#include "MathUtils.h"
#include "Utils2D.h"
#include <iostream>

using namespace softengine;

void Primitive2DRenderer::RenderVertex(
	RenderSurface& surface,
	Vertex2D& vertex)
{
	surface.SetPixelValue(
		vertex.Position.X(),
		vertex.Position.Y(),
		vertex.VertColor
	);
}

void Primitive2DRenderer::RenderPoint(
	RenderSurface& surface,
	Point2D& point)
{
	RenderVertex(
		surface,
		Utils2D::TransformVertexFor2D(
			point.Vertex(),
			point.Transform()
		)
	);
}

void Primitive2DRenderer::RenderLine(
	RenderSurface& surface, 
	Line2D& line)
{
	int yMax, yMin;
	RenderLinePoints(
		surface,
		Utils2D::TransformVertexFor2D(
			line.V1(),
			line.Transform()
		),
		Utils2D::TransformVertexFor2D(
			line.V2(),
			line.Transform()
		),
		yMax,
		yMin
	);
}

void Primitive2DRenderer::RenderLinePoints(
	RenderSurface& surface,
	Vertex2D& v1, 
	Vertex2D& v2,
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
		double factor = (double)i / (double)steps;
		
		surface.SetPixelValue(
			x,
			y,
			InterpolateColor(
				v1.VertColor,
				v2.VertColor,
				factor
			)
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
	Vertex2D& v1,
	Vertex2D& v2,
	Vertex2D& v3)
{
	// TODO - Make this use vertices

	Vector2D p0 = v1.Position;
	Vector2D p1 = v2.Position;
	Vector2D p2 = v3.Position;

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
				v1.VertColor // TODO - Interpolate colors
			);
		}
	}
}

void RenderTriangleWithTexture(
	RenderSurface& surface,
	Vertex2D& v1,
	Vertex2D& v2,
	Vertex2D& v3,
	Texture& texture)
{
	// TODO
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

	if (polygon.VBO().IndicesSize() < 3)
	{
		throw std::runtime_error("Polygon needs at least 3 vertices");
	}

	for (size_t i = 0; i < polygon.VBO().IndicesSize(); i += 3)
	{
		RenderTriangle(
			surface,
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(i),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(i + 1),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(i + 2),
				polygon.Transform()
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

Color Primitive2DRenderer::InterpolateColor(
	Color c1, 
	Color c2, 
	double factor)
{
	Color4D c1d = c1.GetAs4D();
	Color4D c2d = c2.GetAs4D();

	return 
		Color(
			MathUtils::Interpolate(c1d.r, c2d.r, factor),
			MathUtils::Interpolate(c1d.g, c2d.g, factor),
			MathUtils::Interpolate(c1d.b, c2d.b, factor),
			MathUtils::Interpolate(c1d.a, c2d.a, factor)
		);	
}

bool Primitive2DRenderer::IsValidSpritePixel(Color& color)
{
	Color4B c = color.GetAs4B();
	if (c.r == 164 &&
		c.g == 117 &&
		c.b == 160 &&
		c.a == 255)
	{
		return false;
	}
	else
	{
		return true;
	}
}
