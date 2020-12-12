#pragma once

#include "RenderSurface.h"
#include "Color.h"
#include "Vertex2D.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Triangle2D.h"
#include "Polygon2D.h"
#include "Sprite2D.h"
#include "Texture.h"
#include "SDL.h"

namespace softengine
{
	class Primitive2DRenderer
	{
	public:
		Primitive2DRenderer() = delete;

		static void RenderPoint(
			RenderSurface& surface,
			Point2D& point
		);
		static void RenderLine(
			RenderSurface& surface, 
			Line2D& line
		);
		static void RenderLinePoints(
			RenderSurface& surface,
			Vertex2D p1,
			Vertex2D p2,
			int& yMax,
			int& yMin
		);
		static void RenderTriangle(
			RenderSurface& surface, 
			Triangle2D& triangle
		);
		static void RenderTriangleWithTexture(
			RenderSurface& surface,
			Triangle2D& triangle,
			Texture& texture
		);
		static void RenderPolygon(
			RenderSurface& surface,
			Polygon2D& polygon,
			bool isWireFrame = false
		);
		static void RenderPolygonLines(
			RenderSurface& surface, 
			Polygon2D& polygon
		);
		static void RenderPolygonFilled(
			RenderSurface& surface, 
			Polygon2D& polygon
		);
		static void RenderSprite(
			RenderSurface& surface, 
			Sprite2D& sprite
		);
		static bool IsValidSpritePixel(Color& color);
	};
}