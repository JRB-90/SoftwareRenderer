#include "RasteringTools.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Vertex3D.h"
#include "Color.h"
#include "Texture.h"

using namespace softengine;

std::vector<int> RasteringTools::InterpolateXPixelValues(
	int x0, 
	int y0, 
	int x1, 
	int y1)
{
	return InterpolateYPixelValues(y0, x0, y1, x1);
}

std::vector<int> RasteringTools::InterpolateYPixelValues(
	int x0, 
	int y0, 
	int x1,
	int y1)
{
	std::vector<int> pixels;

	if (x0 == x1)
	{
		pixels.push_back(x0);

		return pixels;
	}

	double grad = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
	double d = (double)y0;

	for (int i = x0; i <= x1; i++)
	{
		pixels.push_back(d);
		d += grad;
	}

	return pixels;
}

Vector3D RasteringTools::FindBaryCentricCoords(
	Vector2D& v1, 
	Vector2D& v2, 
	Vector2D& v3, 
	Vector2D& pos)
{
	double f1 =
		(
			((v2.Y() - v3.Y()) * (pos.X() - v3.X())) +
			((v3.X() - v2.X()) * (pos.Y() - v3.Y()))
		) /
		(
			((v2.Y() - v3.Y()) * (v1.X() - v3.X())) +
			((v3.X() - v2.X()) * (v1.Y() - v3.Y()))
			);

	double f2 =
		(
			((v3.Y() - v1.Y()) * (pos.X() - v3.X())) +
			((v1.X() - v3.X()) * (pos.Y() - v3.Y()))
		) /
		(
			((v2.Y() - v3.Y()) * (v1.X() - v3.X())) +
			((v3.X() - v2.X()) * (v1.Y() - v3.Y()))
		);

	double f3 = 1.0 - f1 - f2;

	return Vector3D(f1, f2, f3);
}

Vector3D RasteringTools::FindBaryCentricCoords(
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3, 
	Vector2D& pos)
{
	return
		FindBaryCentricCoords(
			Vector2D(v1.Position.X(), v1.Position.Y()),
			Vector2D(v2.Position.X(), v2.Position.Y()),
			Vector2D(v3.Position.X(), v3.Position.Y()),
			pos
		);
}

Color RasteringTools::InterpolateColor(
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3, 
	Vector3D& pos)
{
	Color4D c1d = v1.VertColor.GetAs4D();
	Vector4D vert1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = v2.VertColor.GetAs4D();
	Vector4D vert2(c2d.r, c2d.g, c2d.b, c2d.a);
	Color4D c3d = v3.VertColor.GetAs4D();
	Vector4D vert3(c3d.r, c3d.g, c3d.b, c3d.a);

	Vector3D baryCoords =
		RasteringTools::FindBaryCentricCoords(
			v1,
			v2,
			v3,
			Vector2D(pos.X(), pos.Y())
		);

	Vector4D v =
		((vert1 * baryCoords.X()) + (vert2 * baryCoords.Y()) + (vert3 * baryCoords.Z())) /
		(baryCoords.X() + baryCoords.Y() + baryCoords.Z());

	return
		Color(
			v.X(),
			v.Y(),
			v.Z(),
			v.W()
		);
}

Color RasteringTools::InterpolateTexture(
	Vertex3D& v1, 
	Vertex3D& v2, 
	Vertex3D& v3, 
	Vector3D& pos, 
	Texture& texture)
{
	Vector3D baryCoords =
		RasteringTools::FindBaryCentricCoords(
			v1,
			v2,
			v3,
			Vector2D(pos.X(), pos.Y())
		);

	Vector2D v =
		((v1.UVCoord * baryCoords.X()) + (v2.UVCoord * baryCoords.Y()) + (v3.UVCoord * baryCoords.Z())) /
		(baryCoords.X() + baryCoords.Y() + baryCoords.Z());

	int varX = v.X() * (double)texture.Width();
	int varY = v.Y() * (double)texture.Height();

	return
		texture.GetPixel(
			varX,
			varY
		);
}
