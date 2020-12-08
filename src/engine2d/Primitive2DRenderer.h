#pragma once

#include "RenderSurface.h"
#include "Color.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Triangle2D.h"
#include "Polygon2D.h"
#include "Sprite2D.h"
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
			Vector2D p1,
			Vector2D p2,
			Color color,
			int& yMax,
			int& yMin
		);
		static void RenderTriangle(
			RenderSurface& surface, 
			Triangle2D& triangle
		);
		static void RenderPolygon(
			RenderSurface& surface, 
			Polygon2D& polygon
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