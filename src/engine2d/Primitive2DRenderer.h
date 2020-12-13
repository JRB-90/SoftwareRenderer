#pragma once

#include "RenderSurface.h"
#include "Color.h"
#include "Vertex2D.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Line2D.h"
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

		static void RenderVertex(
			RenderSurface& surface,
			Vertex2D& vertex
		);
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
			Vertex2D& v1,
			Vertex2D& v2,
			int& yMax,
			int& yMin
		);
		static void RenderTriangle(
			RenderSurface& surface, 
			Vertex2D& v1,
			Vertex2D& v2,
			Vertex2D& v3
		);
		static void RenderTriangleWithTexture(
			RenderSurface& surface,
			Vertex2D& v1,
			Vertex2D& v2,
			Vertex2D& v3,
			Texture& texture
		);
		static void RenderPolygon(
			RenderSurface& surface,
			Polygon2D& polygon,
			bool isWireFrame = false
		);
		static void RenderPolygonWireFrame(
			RenderSurface& surface, 
			Polygon2D& polygon
		);
		static void RenderPolygonFilled(
			RenderSurface& surface, 
			Polygon2D& polygon
		);
		static void RenderPolygonWithTexture(
			RenderSurface& surface,
			Polygon2D& polygon,
			Texture& texture
		);
		static void RenderSprite(
			RenderSurface& surface, 
			Sprite2D& sprite
		);
		static Color InterpolateColor(
			Color& c1,
			Color& c2,
			double factor
		);
		static Color InterpolateColor(
			Vertex2D& v1,
			Vertex2D& v2,
			Vertex2D& v3,
			Vector2D& pos
		);
		static Color InterpolateTexture(
			Vertex2D& v1,
			Vertex2D& v2,
			Vertex2D& v3,
			Vector2D& pos,
			Texture& texture
		);
		static bool IsValidSpritePixel(Color& color);
	};
}