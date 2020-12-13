#include "Sprite2D.h"

#include "Vertex2D.h"
#include <vector>

using namespace softengine;

Sprite2D::Sprite2D()
  :
	vertices(
		std::vector<size_t> { 0, 1, 2, 1, 3, 2 },
		std::vector<Vertex2D>
		{
			Vertex2D(Vector2D(), Vector2D(0, 0)),
			Vertex2D(Vector2D(), Vector2D(1, 0)),
			Vertex2D(Vector2D(), Vector2D(0, 1)),
			Vertex2D(Vector2D(), Vector2D(1, 1))
		}
	)
{
}

Sprite2D::Sprite2D(Texture texture)
  :
	texture(texture),
	vertices(
		std::vector<size_t> { 0, 1, 2, 1, 3, 2 },
		std::vector<Vertex2D>
		{
			Vertex2D(Vector2D(0, 0), Vector2D(0, 0)),
			Vertex2D(Vector2D(texture.Width(), 0), Vector2D(1, 0)),
			Vertex2D(Vector2D(0, texture.Height()), Vector2D(0, 1)),
			Vertex2D(Vector2D(texture.Width(), texture.Height()), Vector2D(1, 1))
		}
	)
{
}

Sprite2D::Sprite2D(
	Texture texture,
	Frame2D transform)
  :
	texture(texture),
	vertices(
		std::vector<size_t> { 0, 1, 2, 1, 3, 2 },
		std::vector<Vertex2D>
		{
			Vertex2D(Vector2D(0, 0), Vector2D(0, 0)),
				Vertex2D(Vector2D(texture.Width(), 0), Vector2D(1, 0)),
				Vertex2D(Vector2D(0, texture.Height()), Vector2D(0, 1)),
				Vertex2D(Vector2D(texture.Width(), texture.Height()), Vector2D(1, 1))
		},
		transform
	)
{
}

Color Sprite2D::GetPixel(
	size_t x,
	size_t y)
{
	return texture.GetPixel(x, y);
}
