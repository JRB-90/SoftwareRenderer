#pragma once

#include "Vector2D.h"
#include "Color.h"

namespace softengine
{
	struct Vertex2D
	{
		Vector2D Position;
		Vector2D UVCoord;
		Color VertColor;

		Vertex2D()
		{
			Position = Vector2D(0.0, 0.0);
			UVCoord = Vector2D(-1, -1);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex2D(Vector2D position)
		{
			Position = position;
			UVCoord = Vector2D(-1, -1);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex2D(
			Vector2D position,
			Vector2D uvCoord)
		{
			Position = position;
			UVCoord = uvCoord;
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex2D(
			Vector2D position,
			Color vertColor)
		{
			Position = position;
			UVCoord = Vector2D(-1, -1);
			VertColor = vertColor;
		}

		Vertex2D(
			Vector2D position,
			Vector2D uvCoord,
			Color vertColor)
		{
			Position = position;
			UVCoord = uvCoord;
			VertColor = vertColor;
		}
	};
}