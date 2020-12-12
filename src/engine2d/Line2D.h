#pragma once

#include "Vertex2D.h"
#include "Frame2D.h"
#include "Color.h"

namespace softengine
{
	class Line2D
	{
	public:
		Line2D(const Line2D& line);
		Line2D(
			Vertex2D v1,
			Vertex2D v2
		);
		Line2D(
			Vertex2D v1,
			Vertex2D v2,
			Frame2D transform
		);
		Line2D(
			Vertex2D v1,
			Vertex2D v2,
			uint16_t width
		);
		Line2D(
			Vertex2D v1,
			Vertex2D v2,
			Frame2D transform,
			uint16_t width
		);
		
		Vertex2D& V1() { return v1; }
		void V1(Vertex2D& v1) { this->v1 = v1; }
		Vertex2D& V2() { return v2; }
		void V2(Vertex2D& v2) { this->v2 = v2; }
		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }
		uint16_t Width() { return width; }
		void Width(uint16_t width) { this->width = width; }

		static bool DoIntersect(
			const Line2D& l1,
			const Line2D& l2
		);

	private:
		Vertex2D v1;
		Vertex2D v2;
		Frame2D transform;
		uint16_t width;
	};
}