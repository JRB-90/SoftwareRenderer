#pragma once

#include "Vector2D.h"
#include "Vector3D.h"
#include "Color.h"

namespace softengine
{
	struct Vertex3D
	{
		Vector3D Position;
		Vector2D UVCoord;
		Vector3D Normal;
		Color VertColor;

		Vertex3D()
		{
			Position = Vector3D(0.0, 0.0, 0.0);
			UVCoord = Vector2D(-1, -1);
			Normal = Vector3D(0.0, 0.0, 0.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex3D(Vector3D position)
		{
			Position = position;
			UVCoord = Vector2D(-1, -1);
			Normal = Vector3D(0.0, 0.0, 0.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex3D(
			Vector3D position,
			Vector2D uvCoord)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = Vector3D(0.0, 0.0, 0.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex3D(
			Vector3D position,
			Vector3D normal)
		{
			Position = position;
			UVCoord = Vector2D(-1, -1);
			Normal = normal;
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex3D(
			Vector3D position,
			Color vertColor)
		{
			Position = position;
			UVCoord = Vector2D(-1, -1);
			Normal = Vector3D(0.0, 0.0, 0.0);
			VertColor = vertColor;
		}

		Vertex3D(
			Vector3D position,
			Vector2D uvCoord,
			Vector3D normal)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = normal;
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex3D(
			Vector3D position,
			Vector2D uvCoord,
			Color vertColor)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = Vector3D(0.0, 0.0, 0.0);
			VertColor = vertColor;
		}

		Vertex3D(
			Vector3D position,
			Vector2D uvCoord,
			Vector3D normal,
			Color vertColor)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = normal;
			VertColor = vertColor;
		}
	};
}