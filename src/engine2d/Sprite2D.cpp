#include "Sprite2D.h"

using namespace softengine;

Sprite2D::Sprite2D()
{
}

Sprite2D::Sprite2D(Texture& texture)
  :
	texture(texture)
{
}

Color Sprite2D::GetPixel(
	size_t x,
	size_t y)
{
	return texture.GetPixel(x, y);
}
