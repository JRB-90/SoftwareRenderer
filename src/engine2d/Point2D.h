#pragma once

#include "Vector2D.h"
#include "Vertex2D.h"
#include "Frame2D.h"

namespace softengine
{
	class Point2D
	{
	public:
		Point2D();
		Point2D(const Point2D& point);
		Point2D(Vertex2D vertex);
		Point2D(
			Vertex2D vertex,
			Frame2D transform
		);
		Point2D(
			Vertex2D vertex,
			uint16_t size
		);
		Point2D(
			Vertex2D vertex,
			Frame2D transform,
			uint16_t size
		);

		Vertex2D& Vertex() { return vertex; }
		void Vertex(Vertex2D& vertex) { this->vertex = vertex; }
		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }
		uint16_t Size() { return size; }
		void Size(uint16_t size) { this->size = size; }

	private:
		Vertex2D vertex;
		Frame2D transform;
		uint16_t size;
	};
}