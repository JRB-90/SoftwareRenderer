#pragma once

#include <Point2D.h>
#include <Line2D.h>
#include <vector>

namespace softengine
{
	class Scene2D
	{
	public:
		Scene2D();

		void Clear();

		std::vector<Point2D>& Points() { return points; }
		std::vector<Line2D>& Lines() { return lines; }

	private:
		std::vector<Point2D> points;
		std::vector<Line2D> lines;
	};
}