#pragma once

#include "Vector2D.h"
#include "Frame2D.h"
#include "Color.h"
#include <vector>

namespace softengine
{
	class Polygon2D
	{
	public:
		Polygon2D();
		Polygon2D(const Polygon2D& polygon);
		Polygon2D(Color color);
		Polygon2D(std::vector<Vector2D> points);
		Polygon2D(
			std::vector<Vector2D> points,
			Color color);

		void ClearPoints();
		void AddPoint(Vector2D& point);

		const std::vector<Vector2D> Points() const { return points; }
		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }
		Color GetColor() const { return color; }
		void SetColor(Color color) { this->color = color; }
		bool IsValid() const { return isValid; }

	private:
		std::vector<Vector2D> points;
		Frame2D transform;
		Color color;
		bool isValid;

		void CheckIsValid();
	};
}