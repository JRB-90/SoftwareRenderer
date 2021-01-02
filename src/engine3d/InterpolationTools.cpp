#include "InterpolationTools.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Vertex3D.h"
#include "Vertex4D.h"
#include "Color.h"
#include "Texture.h"

using namespace softengine;

std::vector<int> InterpolationTools::InterpolateXPixelValues(
	int x0,
	int y0,
	int x1,
	int y1)
{
	return InterpolateYPixelValues(y0, x0, y1, x1);
}

std::vector<int> InterpolationTools::InterpolateYPixelValues(
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

Vector3D InterpolationTools::FindBaryCentricFactors(
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

	return Vector3D(f1, f2, f3) / (f1 + f2 + f3);
}

Vector3D InterpolationTools::FindBaryCentricFactors(
	Vector3D& v1,
	Vector3D& v2,
	Vector3D& v3,
	Vector3D& pos)
{
	return
		FindBaryCentricFactors(
			Vector2D(v1.X(), v1.Y()),
			Vector2D(v2.X(), v2.Y()),
			Vector2D(v3.X(), v3.Y()),
			Vector2D(pos.X(), pos.Y())
		);
}

Vector3D InterpolationTools::FindBaryCentricFactors(
	Vector4D& v1,
	Vector4D& v2,
	Vector4D& v3,
	Vector4D& pos)
{
	return
		FindBaryCentricFactors(
			Vector2D(v1.X(), v1.Y()),
			Vector2D(v2.X(), v2.Y()),
			Vector2D(v3.X(), v3.Y()),
			Vector2D(pos.X(), pos.Y())
		);
}

Vector3D InterpolationTools::FindBaryCentricFactors(
	Vertex3D& v1,
	Vertex3D& v2,
	Vertex3D& v3,
	Vector2D& pos)
{
	return
		FindBaryCentricFactors(
			Vector2D(v1.Position.X(), v1.Position.Y()),
			Vector2D(v2.Position.X(), v2.Position.Y()),
			Vector2D(v3.Position.X(), v3.Position.Y()),
			Vector2D(pos.X(), pos.Y())
		);
}

Vector4D InterpolationTools::InterpolateVec4(
	Vector3D& baryCoords,
	Vector4D& v1,
	Vector4D& v2,
	Vector4D& v3)
{
	Vector4D posInterp =
		v1 * baryCoords.X() +
		v2 * baryCoords.Y() +
		v3 * baryCoords.Z();

	return posInterp;
}

Vector4D InterpolationTools::InterpolateVec4PerspCorrect(
	Vector3D& baryCoords,
	Vector4D& v1,
	Vector4D& v2,
	Vector4D& v3,
	Vector4D& fragment)
{
	Vector4D posInterp =
		(v1 * baryCoords.X()) / fragment.Z() +
		(v2 * baryCoords.Y()) / fragment.Z() +
		(v3 * baryCoords.Z()) / fragment.Z();

	double zInterp =
		(1 / fragment.Z()) * baryCoords.X() +
		(1 / fragment.Z()) * baryCoords.Y() +
		(1 / fragment.Z()) * baryCoords.Z();
	posInterp = posInterp / zInterp;

	return posInterp;
}

Vector4D InterpolationTools::InterpolateNormal(
	Vector3D& baryCoords,
	Vertex4D& v1,
	Vertex4D& v2,
	Vertex4D& v3,
	bool perspectiveCorrect)
{
	if (!perspectiveCorrect)
	{
		Vector4D normInterp =
			v1.Normal * baryCoords.X() +
			v2.Normal * baryCoords.Y() +
			v3.Normal * baryCoords.Z();

		return normInterp;
	}
	else
	{
		Vector4D normInterp =
			(v1.Normal * baryCoords.X()) / v1.Position.Z() +
			(v2.Normal * baryCoords.Y()) / v2.Position.Z() +
			(v3.Normal * baryCoords.Z()) / v3.Position.Z();

		double zInterp =
			(1 / v1.Position.Z()) * baryCoords.X() +
			(1 / v2.Position.Z()) * baryCoords.Y() +
			(1 / v3.Position.Z()) * baryCoords.Z();
		normInterp = normInterp / zInterp;

		return normInterp;
	}
}

Color InterpolationTools::InterpolateColor(
	Vector3D& baryCoords,
	Vertex4D& v1,
	Vertex4D& v2,
	Vertex4D& v3,
	Vector4D& pos,
	bool perspectiveCorrect)
{
	Color4D c1d = v1.VertColor.GetAs4D();
	Vector4D vc1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = v2.VertColor.GetAs4D();
	Vector4D vc2(c2d.r, c2d.g, c2d.b, c2d.a);
	Color4D c3d = v3.VertColor.GetAs4D();
	Vector4D vc3(c3d.r, c3d.g, c3d.b, c3d.a);

	if (!perspectiveCorrect)
	{
		Vector4D colInterp =
			vc1 * baryCoords.X() +
			vc2 * baryCoords.Y() +
			vc3 * baryCoords.Z();

		return
			Color(
				colInterp.X(),
				colInterp.Y(),
				colInterp.Z(),
				colInterp.W()
			);
	}
	else
	{
		Vector4D colInterp =
			(vc1 * baryCoords.X()) / v1.Position.Z() +
			(vc2 * baryCoords.Y()) / v2.Position.Z() +
			(vc3 * baryCoords.Z()) / v3.Position.Z();

		double zInterp =
			(1 / v1.Position.Z()) * baryCoords.X() +
			(1 / v2.Position.Z()) * baryCoords.Y() +
			(1 / v3.Position.Z()) * baryCoords.Z();
		colInterp = colInterp / zInterp;

		return
			Color(
				colInterp.X(),
				colInterp.Y(),
				colInterp.Z(),
				colInterp.W()
			);
	}
}

Color InterpolationTools::InterpolateTexture(
	Vector3D& baryCoords,
	Vertex4D& v1,
	Vertex4D& v2,
	Vertex4D& v3,
	Vector4D& pos,
	Texture& texture,
	bool perspectiveCorrect)
{
	if (!perspectiveCorrect)
	{
		Vector4D texInterp =
			v1.UVCoord * baryCoords.X() +
			v2.UVCoord * baryCoords.Y() +
			v3.UVCoord * baryCoords.Z();

		return
			texture.GetPixel(
				texInterp.X() * (double)texture.Width(),
				texInterp.Y() * (double)texture.Height()
			);
	}
	else
	{
		Vector4D texInterp =
			(v1.UVCoord * baryCoords.X()) / v1.Position.Z() +
			(v2.UVCoord * baryCoords.Y()) / v2.Position.Z() +
			(v3.UVCoord * baryCoords.Z()) / v3.Position.Z();

		double zInterp =
			(1 / v1.Position.Z()) * baryCoords.X() +
			(1 / v2.Position.Z()) * baryCoords.Y() +
			(1 / v3.Position.Z()) * baryCoords.Z();
		texInterp = texInterp / zInterp;

		return
			texture.GetPixel(
				texInterp.X() * (double)texture.Width(),
				texInterp.Y() * (double)texture.Height()
			);
	}
}
