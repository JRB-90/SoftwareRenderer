#include "Primitive2DRenderer.h"

#include "MathUtils.h"
#include "Utils2D.h"
#include "Vector4D.h"
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
			Vector2D cur(x, y);
			Color c = InterpolateColor(
				v1,
				v2,
				v3,
				cur
			);

			surface.SetPixelValue(
				x,
				y,
				c
			);
		}
	}
}

void Primitive2DRenderer::RenderTriangleWithTexture(
	RenderSurface& surface, 
	Vertex2D& v1, 
	Vertex2D& v2, 
	Vertex2D& v3, 
	Texture& texture)
{
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
			Color c = InterpolateTexture(
				v1,
				v2,
				v3,
				Vector2D(x, y),
				texture
			);

			if (IsValidSpritePixel(c))
			{
				surface.SetPixelValue(
					x,
					y,
					c
				);
			}
		}
	}
}

void Primitive2DRenderer::RenderPolygon(
	RenderSurface& surface, 
	Polygon2D& polygon,
	bool isWireFrame)
{
	if (isWireFrame)
	{
		RenderPolygonWireFrame(
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

void Primitive2DRenderer::RenderPolygonWireFrame(
	RenderSurface& surface, 
	Polygon2D& polygon)
{
	switch (polygon.GetDrawType())
	{
	case DrawType::Points:
		for (size_t i = 0; i < polygon.VBO().IndicesSize(); i++)
		{
			size_t vertexIndex = polygon.VBO().Indices(i);
			Vertex2D vertex = polygon.VBO().Vertices(vertexIndex);

			RenderPoint(
				surface,
				Point2D(
					polygon.VBO().Vertices(vertexIndex),
					polygon.Transform()
				)
			);
		}
		break;
	case DrawType::Lines:
		for (size_t i = 0; i < polygon.VBO().IndicesSize() - 1; i += 2)
		{
			size_t vertexIndex1 = polygon.VBO().Indices(i);
			size_t vertexIndex2 = polygon.VBO().Indices(i + 1);
			Line2D line(
				polygon.VBO().Vertices(vertexIndex1),
				polygon.VBO().Vertices(vertexIndex2),
				polygon.Transform()
			);

			RenderLine(surface, line);
		}
		break;
	case DrawType::Triangles:
		for (size_t i = 0; i < polygon.VBO().IndicesSize() - 2; i += 3)
		{
			size_t vertexIndex1 = polygon.VBO().Indices(i);
			size_t vertexIndex2 = polygon.VBO().Indices(i + 1);
			size_t vertexIndex3 = polygon.VBO().Indices(i + 2);

			Line2D l1(
				polygon.VBO().Vertices(vertexIndex1),
				polygon.VBO().Vertices(vertexIndex2),
				polygon.Transform()
			);

			Line2D l2(
				polygon.VBO().Vertices(vertexIndex2),
				polygon.VBO().Vertices(vertexIndex3),
				polygon.Transform()
			);

			Line2D l3(
				polygon.VBO().Vertices(vertexIndex3),
				polygon.VBO().Vertices(vertexIndex1),
				polygon.Transform()
			);

			RenderLine(surface, l1);
			RenderLine(surface, l2);
			RenderLine(surface, l3);
		}
		break;
	case DrawType::Quads:
		// TODO
		break;
	default:
		break;
	}
}

void Primitive2DRenderer::RenderPolygonFilled(
	RenderSurface& surface,
	Polygon2D& polygon)
{
	for (size_t i = 0; i < polygon.VBO().IndicesSize() - 2; i += 3)
	{
		size_t vertexIndex1 = polygon.VBO().Indices(i);
		size_t vertexIndex2 = polygon.VBO().Indices(i + 1);
		size_t vertexIndex3 = polygon.VBO().Indices(i + 2);

		RenderTriangle(
			surface,
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex1),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex2),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex3),
				polygon.Transform()
			)
		);
	}
}

void Primitive2DRenderer::RenderPolygonWithTexture(
	RenderSurface& surface, 
	Polygon2D& polygon, 
	Texture& texture)
{
	// TODO - Test
	for (size_t i = 0; i < polygon.VBO().IndicesSize() - 2; i += 3)
	{
		size_t vertexIndex1 = polygon.VBO().Indices(i);
		size_t vertexIndex2 = polygon.VBO().Indices(i + 1);
		size_t vertexIndex3 = polygon.VBO().Indices(i + 2);

		RenderTriangleWithTexture(
			surface,
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex1),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex2),
				polygon.Transform()
			),
			Utils2D::TransformVertexFor2D(
				polygon.VBO().Vertices(vertexIndex3),
				polygon.Transform()
			),
			texture
		);
	}
}

void Primitive2DRenderer::RenderSprite(
	RenderSurface& surface, 
	Sprite2D& sprite)
{
	Polygon2D p = sprite.Vertices();

	RenderTriangleWithTexture(
		surface,
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(0),
			sprite.Transform()
		),
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(1),
			sprite.Transform()
		),
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(2),
			sprite.Transform()
		),
		sprite.GetTexture()
	);

	RenderTriangleWithTexture(
		surface,
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(1),
			sprite.Transform()
		),
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(3),
			sprite.Transform()
		),
		Utils2D::TransformVertexFor2D(
			p.VBO().Vertices(2),
			sprite.Transform()
		),
		sprite.GetTexture()
	);
}

Color Primitive2DRenderer::InterpolateColor(
	Color& c1, 
	Color& c2, 
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

Color Primitive2DRenderer::InterpolateColor(Vertex2D& v1, Vertex2D& v2, Vertex2D& v3, Vector2D& pos)
{
	double f1 =
		(
			((v2.Position.Y() - v3.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (pos.Y() - v3.Position.Y()))
			) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
			);

	double f2 =
		(
			((v3.Position.Y() - v1.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v1.Position.X() - v3.Position.X()) * (pos.Y() - v3.Position.Y()))
			) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
			);

	double f3 = 1.0 - f1 - f2;

	Color4D c1d = v1.VertColor.GetAs4D();
	Vector4D vert1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = v2.VertColor.GetAs4D();
	Vector4D vert2(c2d.r, c2d.g, c2d.b, c2d.a);
	Color4D c3d = v3.VertColor.GetAs4D();
	Vector4D vert3(c3d.r, c3d.g, c3d.b, c3d.a);

	Vector4D v =
		((vert1 * f1) + (vert2 * f2) + (vert3 * f3)) /
		(f1 + f2 + f3);

	return
		Color(
			v.X(),
			v.Y(),
			v.Z(),
			v.W()
		);
}

Color Primitive2DRenderer::InterpolateTexture(
	Vertex2D& v1, 
	Vertex2D& v2, 
	Vertex2D& v3, 
	Vector2D& pos, 
	Texture& texture)
{
	double f1 = 
		(
			((v2.Position.Y() - v3.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (pos.Y() - v3.Position.Y()))
		) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f2 =
		(
			((v3.Position.Y() - v1.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v1.Position.X() - v3.Position.X()) * (pos.Y() - v3.Position.Y()))
			) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f3 = 1.0 - f1 - f2;

	Vector2D v =
		((v1.UVCoord * f1) + (v2.UVCoord * f2) + (v3.UVCoord * f3)) /
		(f1 + f2 + f3);

	int varx = v.X() * (double)texture.Width();
	int vary = v.Y() * (double)texture.Height();

	return 
		texture.GetPixel(
			v.X() * (double)texture.Width(), 
			v.Y() * (double)texture.Height()
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
