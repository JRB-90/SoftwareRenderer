#pragma once

#include "VBO2D.h"
#include "Frame2D.h"
#include "DrawType.h"
#include <vector>

namespace softengine
{
	class Polygon2D
	{
	public:
		Polygon2D();
		Polygon2D(const Polygon2D& polygon);
		Polygon2D(
			std::vector<size_t> indices,
			std::vector<Vertex2D> vertices
		);
		Polygon2D(
			std::vector<size_t> indices,
			std::vector<Vertex2D> vertices,
			DrawType drawType
		);
		Polygon2D(
			std::vector<size_t> indices,
			std::vector<Vertex2D> vertices,
			Frame2D transform
		);
		Polygon2D(
			std::vector<size_t> indices,
			std::vector<Vertex2D> vertices,
			DrawType drawType,
			Frame2D transform
		);

		VBO2D& VBO() { return vbo; }
		void VBO(VBO2D& vbo) { this->vbo = vbo; }
		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }
		DrawType GetDrawType() { return drawType; }
		void SetDrawType(DrawType drawType) { this->drawType = drawType; }

	private:
		VBO2D vbo;
		Frame2D transform;
		DrawType drawType;
	};
}