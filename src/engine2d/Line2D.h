#pragma once

#include "Vector2D.h"
#include "Frame2D.h"
#include "Color.h"

namespace softengine
{
	class Line2D
	{
	public:
		Line2D(const Line2D& line);
		Line2D(
			Vector2D p1,
			Vector2D p2
		);
		Line2D(
			Vector2D p1,
			Vector2D p2,
			Color color
		);
		Line2D(
			Vector2D p1,
			Vector2D p2,
			uint16_t width
		);
		Line2D(
			Vector2D p1,
			Vector2D p2,
			Color color,
			uint16_t width
		);
		
		Vector2D& P1() { return p1; }
		void P1(Vector2D& p1) { this->p1 = p1; }
		Vector2D& P2() { return p2; }
		void P2(Vector2D& p1) { this->p2 = p2; }
		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }
		Color& GetColor() { return color; }
		void SetColor(Color& color) { this->color = color; }
		uint16_t Width() { return width; }
		void Width(uint16_t width) { this->width = width; }

		static bool DoIntersect(
			const Line2D& l1,
			const Line2D& l2
		);

	private:
		Vector2D p1;
		Vector2D p2;
		Frame2D transform;
		Color color;
		uint16_t width;
	};
}