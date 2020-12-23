#pragma once

#include "Vertex3D.h"
#include "Vector4D.h"
#include "Color.h"

namespace softengine
{
	struct Vertex4D
	{
		Vector4D Position;
		Vector4D UVCoord;
		Vector4D Normal;
		Color VertColor;

		Vertex4D()
		{
			Position = Vector4D(0.0, 0.0, 0.0, 1.0);
			UVCoord = Vector4D(-1.0, -1.0, 0.0, 1.0);
			Normal = Vector4D(0.0, 0.0, 0.0, 1.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex4D(const Vertex4D& vertex)
		{
			Position = vertex.Position;
			UVCoord = vertex.UVCoord;
			Normal = vertex.Normal;
			VertColor = vertex.VertColor;
		}

		Vertex4D(Vector4D position)
		{
			Position = position;
			UVCoord = Vector4D(-1.0, -1.0, 0.0, 1.0);
			Normal = Vector4D(0.0, 0.0, 0.0, 1.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex4D(
			Vector4D position,
			Vector4D uvCoord)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = Vector4D(0.0, 0.0, 0.0, 1.0);
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex4D(
			Vector4D position,
			Color vertColor)
		{
			Position = position;
			UVCoord = Vector4D(-1.0, -1.0, 0.0, 1.0);
			Normal = Vector4D(0.0, 0.0, 0.0, 1.0);
			VertColor = vertColor;
		}

		Vertex4D(
			Vector4D position,
			Vector4D uvCoord,
			Vector4D normal)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = normal;
			VertColor = Color(0.0, 0.0, 0.0, 0.0);
		}

		Vertex4D(
			Vector4D position,
			Vector4D uvCoord,
			Color vertColor)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = Vector4D(0.0, 0.0, 0.0, 1.0);
			VertColor = vertColor;
		}

		Vertex4D(
			Vector4D position,
			Vector4D uvCoord,
			Vector4D normal,
			Color vertColor)
		{
			Position = position;
			UVCoord = uvCoord;
			Normal = normal;
			VertColor = vertColor;
		}

		Vertex4D(Vertex3D vertex)
		{
			Position = Vector4D(
				vertex.Position.X(),
				vertex.Position.Y(),
				vertex.Position.Z(),
				1.0
			);
			UVCoord = Vector4D(
				vertex.UVCoord.X(),
				vertex.UVCoord.Y(),
				0.0,
				1.0
			);
			Normal = Vector4D(
				vertex.Normal.X(),
				vertex.Normal.Y(),
				vertex.Normal.Z(),
				1.0
			);
			VertColor = vertex.VertColor;
		}
	};
}