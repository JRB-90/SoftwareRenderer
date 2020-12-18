#pragma once

#include "VBO3D.h"
#include "Frame3D.h"
#include "DrawType.h"
#include <vector>

namespace softengine
{
	class Mesh3D
	{
	public:
		Mesh3D();
		Mesh3D(const Mesh3D& mesh);
		Mesh3D(
			std::vector<size_t> indices,
			std::vector<Vertex3D> vertices
		);
		Mesh3D(
			std::vector<size_t> indices,
			std::vector<Vertex3D> vertices,
			DrawType drawType
		);
		Mesh3D(
			std::vector<size_t> indices,
			std::vector<Vertex3D> vertices,
			Frame3D transform
		);
		Mesh3D(
			std::vector<size_t> indices,
			std::vector<Vertex3D> vertices,
			DrawType drawType,
			Frame3D transform
		);

		VBO3D& VBO() { return vbo; }
		void VBO(VBO3D& vbo) { this->vbo = vbo; }
		Frame3D& Transform() { return transform; }
		void Transform(Frame3D& transform) { this->transform = transform; }
		DrawType GetDrawType() { return drawType; }
		void SetDrawType(DrawType drawType) { this->drawType = drawType; }

	private:
		VBO3D vbo;
		Frame3D transform;
		DrawType drawType;
	};
}