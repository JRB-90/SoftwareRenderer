#pragma once

#include "Vector2D.h"
#include "Color.h"
#include <vector>

namespace softengine
{
	class Polygon2D
	{
	public:
		Polygon2D();
		Polygon2D(Color color);
		Polygon2D(std::vector<Vector2D> points);
		Polygon2D(
			std::vector<Vector2D> points,
			Color color);

		void ClearPoints();
		void AddPoint(Vector2D& point);

		std::vector<Vector2D> Points() const { return points; }
		Color GetColor() const { return color; }
		void SetColor(Color color) { this->color = color; }

	private:
		std::vector<Vector2D> points;
		Color color;
	};
}