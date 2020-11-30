#pragma once

#include "Vector2D.h"
#include "Color.h"

namespace softengine
{
	class Triangle2D
	{
	public:
		Triangle2D(const Triangle2D& triangle);
		Triangle2D(
			Vector2D p1,
			Vector2D p2,
			Vector2D p3
		);
		Triangle2D(
			Vector2D p1,
			Vector2D p2,
			Vector2D p3,
			Color color
		);

		Vector2D& P1() { return p1; }
		void P1(Vector2D& p1) { this->p1 = p1; }
		Vector2D& P2() { return p2; }
		void P2(Vector2D& p1) { this->p2 = p2; }
		Vector2D& P3() { return p3; }
		void P3(Vector2D& p1) { this->p3 = p3; }
		Color& GetColor() { return color; }
		void SetColor(Color& color) { this->color = color; }

	private:
		Vector2D p1;
		Vector2D p2;
		Vector2D p3;
		Color color;
	};
}