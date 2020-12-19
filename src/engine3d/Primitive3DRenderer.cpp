#include "Primitive3DRenderer.h"
#include "Vector2D.h"
#include "Vector4D.h"
#include "DrawType.h"
#include "Utils2D.h"

using namespace softengine;

void Primitive3DRenderer::RenderMesh(
	RenderSurface& surface,
	Mesh3D& mesh,
	Camera& camera)
{
	switch (mesh.GetDrawType())
	{
	case DrawType::Points:
		for (size_t i = 0; i < mesh.VBO().IndicesSize(); i++)
		{
			size_t vertexIndex = mesh.VBO().Indices(i);
			Vertex3D vertex = mesh.VBO().Vertices(vertexIndex);
			RenderVertex(
				surface,
				VertexShader(
					vertex,
					mesh.Transform(),
					camera
				)
			);
		}
		break;
	case DrawType::Lines:
		for (size_t i = 0; i < mesh.VBO().IndicesSize() - 1; i += 2)
		{
			size_t vertexIndex1 = mesh.VBO().Indices(i);
			size_t vertexIndex2 = mesh.VBO().Indices(i + 1);

			RenderLine(
				surface,
				VertexShader(
					mesh.VBO().Vertices(vertexIndex1),
					mesh.Transform(),
					camera
				),
				VertexShader(
					mesh.VBO().Vertices(vertexIndex2),
					mesh.Transform(),
					camera
				)
			);
		}
		break;
	case DrawType::Triangles:
		for (size_t i = 0; i < mesh.VBO().IndicesSize() - 2; i += 3)
		{
			size_t vertexIndex1 = mesh.VBO().Indices(i);
			size_t vertexIndex2 = mesh.VBO().Indices(i + 1);
			size_t vertexIndex3 = mesh.VBO().Indices(i + 2);

			RenderTriangle(
				surface,
				camera,
				VertexShader(
					mesh.VBO().Vertices(vertexIndex1),
					mesh.Transform(),
					camera
				),
				VertexShader(
					mesh.VBO().Vertices(vertexIndex2),
					mesh.Transform(),
					camera
				),
				VertexShader(
					mesh.VBO().Vertices(vertexIndex3),
					mesh.Transform(),
					camera
				),
				mesh.GetTextrue()
			);
		}
		break;
	case DrawType::Quads:
		// TODO
		break;
	default:
		break;
	}
}

void Primitive3DRenderer::RenderVertex(
	RenderSurface& surface, 
	Vertex3D& vertex)
{
	if (
		surface.PassesZCheck(
			vertex.Position.X(),
			vertex.Position.Y(),
			vertex.Position.Z()
		)
	)
	{
		surface.SetPixelValue(
			vertex.Position.X(),
			vertex.Position.Y(),
			vertex.VertColor
		);
	}
}

void Primitive3DRenderer::RenderLine(
	RenderSurface& surface, 
	Vertex3D& v1, 
	Vertex3D& v2)
{
	double x = v1.Position.X();
	double y = v1.Position.Y();
	double z = v1.Position.Z();
	double dx = v2.Position.X() - v1.Position.X();
	double dy = v2.Position.Y() - v1.Position.Y();
	double dz = v2.Position.Z() - v1.Position.Z();
	int steps;

	if (std::abs(dx) > std::abs(dy))
	{
		steps = (int)std::abs(dx);
	}
	else
	{
		steps = (int)std::abs(dy);
	}

	double xInc = dx / (double)steps;
	double yInc = dy / (double)steps;
	double zInc = dz / (double)steps;

	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yInc;
		z += zInc;
		double factor = (double)i / (double)steps;

		if (
			surface.PassesZCheck(
				x,
				y,
				z
			)
		)
		{
			surface.SetPixelValue(
				x,
				y,
				Color::InterpolateColor(
					v1.VertColor,
					v2.VertColor,
					factor
				)
			);
		}
	}
}

void Primitive3DRenderer::RenderTriangle(
	RenderSurface& surface, 
	Camera& camera,
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3,
	Texture& texture)
{
	Vector3D v12 = (v2.Position - v1.Position).Normalised();
	Vector3D v13 = (v3.Position - v1.Position).Normalised();
	Vector3D cross = v12.Cross(v13);
	if (cross.Z() < 0.0)
	{
		return;
	}

	Vector2D p0 = Vector2D(v1.Position.X(), v1.Position.Y());
	Vector2D p1 = Vector2D(v2.Position.X(), v2.Position.Y());
	Vector2D p2 = Vector2D(v3.Position.X(), v3.Position.Y());

	if (p1.Y() < p0.Y())
	{
		Vector2D temp = p1;
		p1 = p0;
		p0 = temp;
	}
	if (p2.Y() < p0.Y())
	{
		Vector2D temp = p2;
		p2 = p0;
		p0 = temp;
	}
	if (p2.Y() < p1.Y())
	{
		Vector2D temp = p2;
		p2 = p1;
		p1 = temp;
	}

	std::vector<int> x01 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p1.X(),
			p1.Y()
		);

	std::vector<int> x12 =
		Utils2D::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p2.X(),
			p2.Y()
		);

	x01.pop_back();
	std::vector<int> x012;
	for (auto x : x01)
	{
		x012.push_back(x);
	}
	for (auto x : x12)
	{
		x012.push_back(x);
	}

	std::vector<int> xLeft;
	std::vector<int> xRight;
	int m = x02.size() / 2;
	if (x02[m] < x012[m])
	{
		xLeft = x02;
		xRight = x012;
	}
	else
	{
		xLeft = x012;
		xRight = x02;
	}

	for (int y = p0.Y(); y < p2.Y(); y++)
	{
		for (int x = xLeft[y - p0.Y()]; x < xRight[y - p0.Y()]; x++)
		{
			double f1 =
				(
					((v2.Position.Y() - v3.Position.Y()) * (x - v3.Position.X())) +
					((v3.Position.X() - v2.Position.X()) * (y - v3.Position.Y()))
					) /
				(
					((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
					((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
					);

			double f2 =
				(
					((v3.Position.Y() - v1.Position.Y()) * (x - v3.Position.X())) +
					((v1.Position.X() - v3.Position.X()) * (y - v3.Position.Y()))
					) /
				(
					((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
					((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
				);

			double f3 = 1.0 - f1 - f2;

			double z = v1.Position.Z() * f1 + v2.Position.Z() * f2 + v3.Position.Z() * f3;
			Vector3D cur(x, y, z);
			Color c = Color::Black;

			if (texture.Height() > 0 &&
				texture.Width() > 0)
			{
				c = InterpolateTexture(
					v1,
					v2,
					v3,
					cur,
					texture
				);

				if (!IsValidSpritePixel(c))
				{
					continue;
				}
			}
			else
			{
				c = InterpolateColor(
					v1,
					v2,
					v3,
					cur
				);
			}

			if (surface.PassesZCheck(x, y, z))
			{
				surface.SetPixelValue(
					x,
					y,
					PixelShader(
						c,
						cur,
						camera
					)
				);
			}
		}
	}
}

Color Primitive3DRenderer::InterpolateColor(
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3, 
	Vector3D& pos)
{
	double f1 =
		(
			((v2.Position.Y() - v3.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (pos.Y() - v3.Position.Y()))
		) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f2 =
		(
			((v3.Position.Y() - v1.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v1.Position.X() - v3.Position.X()) * (pos.Y() - v3.Position.Y()))
		) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f3 = 1.0 - f1 - f2;

	Color4D c1d = v1.VertColor.GetAs4D();
	Vector4D vert1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = v2.VertColor.GetAs4D();
	Vector4D vert2(c2d.r, c2d.g, c2d.b, c2d.a);
	Color4D c3d = v3.VertColor.GetAs4D();
	Vector4D vert3(c3d.r, c3d.g, c3d.b, c3d.a);

	Vector4D v =
		((vert1 * f1) + (vert2 * f2) + (vert3 * f3)) /
		(f1 + f2 + f3);

	return
		Color(
			v.X(),
			v.Y(),
			v.Z(),
			v.W()
		);
}

Color Primitive3DRenderer::InterpolateTexture(
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3, 
	Vector3D& pos, 
	Texture& texture)
{
	double f1 =
		(
			((v2.Position.Y() - v3.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (pos.Y() - v3.Position.Y()))
		) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f2 =
		(
			((v3.Position.Y() - v1.Position.Y()) * (pos.X() - v3.Position.X())) +
			((v1.Position.X() - v3.Position.X()) * (pos.Y() - v3.Position.Y()))
		) /
		(
			((v2.Position.Y() - v3.Position.Y()) * (v1.Position.X() - v3.Position.X())) +
			((v3.Position.X() - v2.Position.X()) * (v1.Position.Y() - v3.Position.Y()))
		);

	double f3 = 1.0 - f1 - f2;

	Vector2D v =
		((v1.UVCoord * f1) + (v2.UVCoord * f2) + (v3.UVCoord * f3)) /
		(f1 + f2 + f3);

	int varX = v.X() * (double)texture.Width();
	int varY = v.Y() * (double)texture.Height();

	return
		texture.GetPixel(
			varX,
			varY
		);
}

bool Primitive3DRenderer::IsValidSpritePixel(Color& color)
{
	Color4B c = color.GetAs4B();
	if (c.r == 164 &&
		c.g == 117 &&
		c.b == 160 &&
		c.a == 255)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Vertex3D Primitive3DRenderer::VertexShader(
	Vertex3D& vertex, 
	Frame3D& model, 
	Camera& camera)
{
	// TODO

	return
		Vertex3D(
			vertex.Position * model,
			vertex.UVCoord,
			vertex.Normal,
			vertex.VertColor
		);
}

Color Primitive3DRenderer::PixelShader(
	Color pixelColor, 
	Vector3D pixelPosition, 
	Camera& camera)
{
	// TODO

	return pixelColor;
}
