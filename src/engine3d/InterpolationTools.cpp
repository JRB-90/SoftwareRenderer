#include "InterpolationTools.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vertex3D.h"
#include "Vertex4D.h"
#include "Texture.h"
#include "Material.h"
#include "RasteringTools.h"

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

InterpolatedFragment InterpolationTools::InterpolateFragment(
	RasterFragment fragment,
	Vertex4D& vertex0,
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	Vertex4D& oV0,
	Vertex4D& oV1,
	Vertex4D& oV2,
	Vector4D& vc0,
	Vector4D& vc1,
	Vector4D& vc2,
	Material& material)
{
	double w0 = fragment.BaryCoords.X();
	double w1 = fragment.BaryCoords.Y();
	double w2 = fragment.BaryCoords.Z();

	double denom = 1.0 / ((double)w0 + (double)w1 + (double)w2);
	double _w0 = (double)w0 * denom;
	double _w1 = (double)w1 * denom;
	double _w2 = (double)w2 * denom;

	double persCorrector = 
		1.0 / 
		(
			_w0 * vertex0.Position.W() +
			_w1 * vertex1.Position.W() + 
			_w2 * vertex2.Position.W()
		);

	_w0 = _w0 * vertex0.Position.W() * persCorrector;
	_w1 = _w1 * vertex1.Position.W() * persCorrector;
	_w2 = _w2 * vertex2.Position.W() * persCorrector;

	Vector4D interpPos = (oV0.Position * w0 + oV1.Position * w1 + oV2.Position * w2) * denom;
	Vector4D interpNorm = (vertex0.Normal * _w0 + vertex1.Normal * _w1 + vertex2.Normal * _w2);
	Vector4D interpTex = (vertex0.UVCoord * _w0 + vertex1.UVCoord * _w1 + vertex2.UVCoord * _w2);
	Color interpColor;

	bool hasTexture =
		material.GetTexture().Height() > 0 &&
		material.GetTexture().Width() > 0;

	if (hasTexture)
	{
		interpColor = material.GetTexture().GetPixel(
			interpTex.X() * (double)material.GetTexture().Width(),
			interpTex.Y() * (double)material.GetTexture().Height()
		);
	}
	else
	{
		Vector4D interpColorVec = (vc0 * _w0 + vc1 * _w1 + vc2 * _w2);
		interpColor = 
			Color(
				interpColorVec.X(), 
				interpColorVec.Y(), 
				interpColorVec.Z(),
				interpColorVec.W()
			);
	}

	return
		InterpolatedFragment(
			fragment.Fragment,
			interpPos,
			interpNorm,
			interpTex,
			interpColor
		);
}

Vector4D InterpolationTools::CalculateFaceNormal(
	Vector4D v0, 
	Vector4D v1, 
	Vector4D v2)
{
	Vector3D oVec3_0 = Vector3D(v0.X(), v0.Y(), v0.Z());
	Vector3D oVec3_1 = Vector3D(v1.X(), v1.Y(), v1.Z());
	Vector3D oVec3_2 = Vector3D(v2.X(), v2.Y(), v2.Z());
	Vector3D oV01 = (oVec3_1 - oVec3_0).Normalised();
	Vector3D oV02 = (oVec3_2 - oVec3_0).Normalised();
	Vector3D oCross = oV01.Cross(oV02).Normalised();
	Vector4D faceNormal(oCross.X(), oCross.Y(), oCross.Z(), 1.0);

	return faceNormal;
}
