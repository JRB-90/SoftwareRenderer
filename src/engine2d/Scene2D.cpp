#include "Scene2D.h"

using namespace softengine;

Scene2D::Scene2D()
{
}

void Scene2D::ClearAll()
{
	points.clear();
	lines.clear();
	polygons.clear();
	sprites.clear();
}
