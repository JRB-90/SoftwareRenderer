#pragma once

#include "Texture.h"
#include "Frame2D.h"
#include "Polygon2D.h"
#include "Color.h"

namespace softengine
{
	class Sprite2D
	{
	public:
		Sprite2D();
		Sprite2D(Texture texture);
		Sprite2D(
			Texture texture,
			Frame2D transform
		);

		Texture& GetTexture() { return texture; }
		const Polygon2D& Vertices() { return vertices; }
		Frame2D& Transform() { return vertices.Transform(); }
		void Transform(Frame2D& transform) { this->vertices.Transform(transform); }

		size_t Width() { return texture.Width(); }
		size_t Height() { return texture.Height(); }
		Color GetPixel(
			size_t x, 
			size_t y
		);

	private:
		Texture texture;
		Polygon2D vertices;
	};
}