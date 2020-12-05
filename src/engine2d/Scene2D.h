#pragma once

#include "IScene.h"
#include <Point2D.h>
#include <Line2D.h>
#include "Polygon2D.h"
#include "Sprite2D.h"
#include <vector>

namespace softengine
{
	class Scene2D : public IScene
	{
	public:
		Scene2D();

		void ClearAll() override;

		std::vector<Point2D>& Points() { return points; }
		std::vector<Line2D>& Lines() { return lines; }
		std::vector<Polygon2D>& Polygons() { return polygons; }
		std::vector<Sprite2D>& Sprites() { return sprites; }

	private:
		std::vector<Point2D> points;
		std::vector<Line2D> lines;
		std::vector<Polygon2D> polygons;
		std::vector<Sprite2D> sprites;
	};
}