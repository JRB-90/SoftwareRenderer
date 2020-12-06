#pragma once

#include "Texture.h"
#include "Frame2D.h"
#include "Color.h"

namespace softengine
{
	class Sprite2D
	{
	public:
		Sprite2D();
		Sprite2D(Texture texture);

		Frame2D& Transform() { return transform; }
		void Transform(Frame2D& transform) { this->transform = transform; }

		size_t Width() { return texture.Width(); }
		size_t Height() { return texture.Height(); }
		Color GetPixel(
			size_t x, 
			size_t y
		);

	private:
		Texture texture;
		Frame2D transform;
	};
}