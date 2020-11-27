#pragma once

#include "Vector2D.h"
#include "Color.h"

namespace softengine
{
	class Point2D
	{
	public:
		Point2D();
		Point2D(const Point2D& point);
		Point2D(Vector2D position);
		Point2D(
			Vector2D position,
			Color color
		);
		Point2D(
			Vector2D position,
			uint16_t size
		);
		Point2D(
			Vector2D position,
			Color color,
			uint16_t size
		);

		Vector2D& Position() { return position; }
		void Position(Vector2D& position) { this->position = position; }
		Color& GetColor() { return color; }
		void SetColor(Color& color) { this->color = color; }
		uint16_t Size() { return size; }
		void Size(uint16_t size) { this->size = size; }

	private:
		Vector2D position;
		Color color;
		uint16_t size;
	};
}