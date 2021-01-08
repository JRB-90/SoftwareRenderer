#include "RasteringTools.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Vertex3D.h"
#include "Vertex4D.h"
#include "Matrix3.h"
#include "Color.h"
#include "Texture.h"
#include "Material.h"
#include "Camera.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "ShaderTools.h"
#include "InterpolationTools.h"
#include <cmath>

#include <omp.h>

using namespace softengine;

bool RasteringTools::PassesClipTest(Vertex4D& v1)
{
	return
		-v1.Position.W() <= v1.Position.X() &&
		v1.Position.X() <= v1.Position.W() &&
		-v1.Position.W() <= v1.Position.Y() &&
		v1.Position.Y() <= v1.Position.W() &&
		-v1.Position.W() <= v1.Position.Z() &&
		v1.Position.Z() <= v1.Position.W();
}

bool RasteringTools::PassesClipTest(VertexShaderOut& out)
{
	return
		-out.vertex.Position.W() <= out.vertex.Position.X() &&
		out.vertex.Position.X() <= out.vertex.Position.W() &&
		-out.vertex.Position.W() <= out.vertex.Position.Y() &&
		out.vertex.Position.Y() <= out.vertex.Position.W() &&
		-out.vertex.Position.W() <= out.vertex.Position.Z() &&
		out.vertex.Position.Z() <= out.vertex.Position.W();
}

void RasteringTools::TranformToRasterSpace(
	Vertex4D& vertex,
	Camera& camera)
{
	// Perspective divide
	vertex.Position.X(vertex.Position.X() / vertex.Position.W());
	vertex.Position.Y(vertex.Position.Y() / vertex.Position.W());
	vertex.Position.Z(vertex.Position.Z() / vertex.Position.W());
	vertex.Position.W(1.0 / vertex.Position.W());

	// Viewport transform
	vertex.Position.X(((vertex.Position.X() + 1) * (camera.Width() / 2)) + 0);
	vertex.Position.Y(((vertex.Position.Y() + 1) * (-camera.Height() / 2)) + 480);
}

void RasteringTools::TranformToRasterSpace(
	VertexShaderOut& out,
	Camera& camera)
{
	// Perspective divide
	out.vertex.Position.X(out.vertex.Position.X() / out.vertex.Position.W());
	out.vertex.Position.Y(out.vertex.Position.Y() / out.vertex.Position.W());
	out.vertex.Position.Z(out.vertex.Position.Z() / out.vertex.Position.W());
	out.vertex.Position.W(1.0 / out.vertex.Position.W());

	// Viewport transform
	out.vertex.Position.X(((out.vertex.Position.X() + 1) * (camera.Width() / 2)) + 0);
	out.vertex.Position.Y(((out.vertex.Position.Y() + 1) * (-camera.Height() / 2)) + 480);
}

bool RasteringTools::PassesDepthCheck(
	RenderSurface& surface,
	Vector3D& fragment,
	DepthCheckMode depthCheckMode)
{
	double zVal = surface.GetZBufferVal(fragment.X(), fragment.Y());
	if (std::isnan(zVal) ||
		fragment.Z() < 0)
	{
		return false;
	}

	switch (depthCheckMode)
	{
	case DepthCheckMode::NoDepthCheck:
		surface.SetZBufferVal(
			fragment.X(),
			fragment.Y(),
			fragment.Z()
		);

		return true;
	case DepthCheckMode::DepthCheckGreaterThan:
		if (fragment.Z() >= zVal)
		{
			surface.SetZBufferVal(
				fragment.X(),
				fragment.Y(),
				fragment.Z()
			);

			return true;
		}
		else
		{
			return false;
		}
	case DepthCheckMode::DepthCheckLessThan:
		if (fragment.Z() <= zVal)
		{
			surface.SetZBufferVal(
				fragment.X(),
				fragment.Y(),
				fragment.Z()
			);

			return true;
		}
		else
		{
			return false;
		}
	default:
		return false;
	}
}

void RasteringTools::PointRasteriser(
	RenderSurface& surface,
	PipelineConfiguration& pipelineConfiguration,
	Camera& camera,
	Vertex4D& vertex,
	SceneLighting& lights,
	Profiler& profiler)
{
	if (!RasteringTools::PassesDepthCheck(
		surface,
		Vector3D(
			vertex.Position.X(),
			vertex.Position.Y(),
			vertex.Position.Z()
		),
		pipelineConfiguration.depthCheckMode)
		)
	{
		return;
	}

	ShaderTools::PixelShader(
		surface,
		camera,
		vertex.Position,
		vertex.Position,
		vertex.Normal,
		Vector4D(),
		vertex.VertColor,
		Material(),
		lights,
		pipelineConfiguration.depthCheckMode,
		profiler
	);
}

void RasteringTools::PointRasteriser(
	PointRasteriserIn in,
	Profiler& profiler)
{
	ShaderTools::PixelShader(
		*in.surface,
		*in.camera,
		in.vertex1->Position,
		in.vertex1->Position,
		in.vertex1->Normal,
		Vector4D(),
		in.vertex1->VertColor,
		Material(),
		*in.lights,
		in.pipelineConfiguration->depthCheckMode,
		profiler
	);
}

void RasteringTools::LineRasteriser(
	RenderSurface& surface,
	PipelineConfiguration& pipelineConfiguration,
	Camera& camera,
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	SceneLighting& lights,
	Profiler& profiler)
{
	double x = vertex1.Position.X();
	double y = vertex1.Position.Y();
	double z = vertex1.Position.Z();
	double dx = vertex2.Position.X() - vertex1.Position.X();
	double dy = vertex2.Position.Y() - vertex1.Position.Y();
	double dz = vertex2.Position.Z() - vertex1.Position.Z();
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
		Vector4D currentPosition(x, y, z, 1.0);

		if (!RasteringTools::PassesDepthCheck(
			surface,
			Vector3D(
				currentPosition.X(),
				currentPosition.Y(),
				currentPosition.Z()
			),
			pipelineConfiguration.depthCheckMode)
			)
		{
			continue;
		}

		ShaderTools::PixelShader(
			surface,
			camera,
			currentPosition,
			currentPosition,
			Vector4D(),
			Vector4D(),
			Color::InterpolateColor(
				vertex1.VertColor,
				vertex2.VertColor,
				factor
			),
			Material(),
			lights,
			pipelineConfiguration.depthCheckMode,
			profiler
		);
	}
}

void RasteringTools::TriangleRasteriser1(
	RenderSurface& surface,
	PipelineConfiguration& pipelineConfiguration,
	Camera& camera,
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	Vertex4D& vertex3,
	Vertex4D& oV1,
	Vertex4D& oV2,
	Vertex4D& oV3,
	Material& material,
	SceneLighting& lights,
	Profiler& profiler)
{
	Vector3D vec3_1 = Vector3D(vertex1.Position.X(), vertex1.Position.Y(), vertex1.Position.Z());
	Vector3D vec3_2 = Vector3D(vertex2.Position.X(), vertex2.Position.Y(), vertex2.Position.Z());
	Vector3D vec3_3 = Vector3D(vertex3.Position.X(), vertex3.Position.Y(), vertex3.Position.Z());
	Vector3D v12 = (vec3_2 - vec3_1).Normalised();
	Vector3D v13 = (vec3_3 - vec3_1).Normalised();
	Vector3D cross = v12.Cross(v13).Normalised();

	Vector3D oVec3_1 = Vector3D(oV1.Position.X(), oV1.Position.Y(), oV1.Position.Z());
	Vector3D oVec3_2 = Vector3D(oV2.Position.X(), oV2.Position.Y(), oV2.Position.Z());
	Vector3D oVec3_3 = Vector3D(oV3.Position.X(), oV3.Position.Y(), oV3.Position.Z());
	Vector3D oV12 = (oVec3_2 - oVec3_1).Normalised();
	Vector3D oV13 = (oVec3_3 - oVec3_1).Normalised();
	Vector3D oCross = oV12.Cross(oV13).Normalised();
	Vector4D faceNormal(oCross.X(), oCross.Y(), oCross.Z(), 1.0);

	if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::Clockwise) &&
		cross.Z() < 0.0)
	{
		return;
	}
	else if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::AntiClockwise) &&
		cross.Z() > 0.0)
	{
		return;
	}

	Vector2D p0 = Vector2D(vertex1.Position.X(), vertex1.Position.Y());
	Vector2D p1 = Vector2D(vertex2.Position.X(), vertex2.Position.Y());
	Vector2D p2 = Vector2D(vertex3.Position.X(), vertex3.Position.Y());

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
		InterpolationTools::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p1.X(),
			p1.Y()
		);

	std::vector<int> x12 =
		InterpolationTools::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		InterpolationTools::InterpolateXPixelValues(
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
			Vector3D baryCoords =
				InterpolationTools::FindBaryCentricFactors(
					vertex1.Position,
					vertex2.Position,
					vertex3.Position,
					Vector4D(x, y, 0.0, 1.0)
				);

			Vector4D fragmentPosition(x, y, 0.0, 1.0);
			Color c = Color::Black;

			Vector4D interpPosition =
				InterpolationTools::InterpolateVec4(
					baryCoords,
					oV1.Position,
					oV2.Position,
					oV3.Position
				);

			Vector4D interpNormal =
				InterpolationTools::InterpolateNormal(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					true
				);

			if (material.GetTexture().Height() > 0 &&
				material.GetTexture().Width() > 0)
			{
				c = InterpolationTools::InterpolateTexture(
					baryCoords,
					oV1,
					oV2,
					oV3,
					fragmentPosition,
					material.GetTexture(),
					true
				);
			}
			else
			{
				c = InterpolationTools::InterpolateColor(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					fragmentPosition,
					true
				);
			}

			if (!RasteringTools::PassesDepthCheck(
				surface,
				Vector3D(
					fragmentPosition.X(),
					fragmentPosition.Y(),
					interpPosition.Z()
				),
				pipelineConfiguration.depthCheckMode)
			)
			{
				continue;
			}

			ShaderTools::PixelShader(
				surface,
				camera,
				fragmentPosition,
				interpPosition,
				interpNormal,
				faceNormal,
				c,
				material,
				lights,
				pipelineConfiguration.depthCheckMode,
				profiler
			);
		}
	}
}

void RasteringTools::TriangleRasteriser2(
	RenderSurface& surface,
	PipelineConfiguration& pipelineConfiguration,
	Camera& camera,
	Vertex4D& vertex0,
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	Vertex4D& oV0,
	Vertex4D& oV1,
	Vertex4D& oV2,
	Material& material,
	SceneLighting& lights,
	Profiler& profiler)
{
	Vector3D v0 = Vector3D(vertex0.Position.X(), vertex0.Position.Y(), vertex0.Position.Z());
	Vector3D v1 = Vector3D(vertex1.Position.X(), vertex1.Position.Y(), vertex1.Position.Z());
	Vector3D v2 = Vector3D(vertex2.Position.X(), vertex2.Position.Y(), vertex2.Position.Z());
	Vector3D v01 = (v1 - v0).Normalised();
	Vector3D v02 = (v2 - v0).Normalised();
	Vector3D cross = v01.Cross(v02).Normalised();

	if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::Clockwise) &&
		cross.Z() < 0.0)
	{
		return;
	}
	else if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::AntiClockwise) &&
		cross.Z() > 0.0)
	{
		return;
	}

	bool hasTexture = 
		material.GetTexture().Height() > 0 &&
		material.GetTexture().Width() > 0;

	// Find face normal
	Vector3D oVec3_0 = Vector3D(oV0.Position.X(), oV0.Position.Y(), oV0.Position.Z());
	Vector3D oVec3_1 = Vector3D(oV1.Position.X(), oV1.Position.Y(), oV1.Position.Z());
	Vector3D oVec3_2 = Vector3D(oV2.Position.X(), oV2.Position.Y(), oV2.Position.Z());
	Vector3D oV01 = (oVec3_1 - oVec3_0).Normalised();
	Vector3D oV02 = (oVec3_2 - oVec3_0).Normalised();
	Vector3D oCross = oV01.Cross(oV02).Normalised();
	Vector4D faceNormal(oCross.X(), oCross.Y(), oCross.Z(), 1.0);

	// Setup some conveinence objects
	Color4D c0d = vertex0.VertColor.GetAs4D();
	Vector4D vc0(c0d.r, c0d.g, c0d.b, c0d.a);
	Color4D c1d = vertex1.VertColor.GetAs4D();
	Vector4D vc1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = vertex2.VertColor.GetAs4D();
	Vector4D vc2(c2d.r, c2d.g, c2d.b, c2d.a);

	// Triangle setup	
	double A01 = v0.Y() - v1.Y();
	double A12 = v1.Y() - v2.Y();
	double A20 = v2.Y() - v0.Y();

	double B01 = v1.X() - v0.X();
	double B12 = v2.X() - v1.X();
	double B20 = v0.X() - v2.X();

	//double C01 = v0.X() * v1.Y() - v0.Y() * v1.X();
	//double C12 = v1.X() * v2.Y() - v1.Y() * v2.X();
	//double C20 = v2.X() * v0.Y() - v2.Y() * v0.X();

	// Barycentric coordinates at minX/minY corner
	double minX = std::min(std::min(v0.X(), v1.X()), v2.X());
	double minY = std::min(std::min(v0.Y(), v1.Y()), v2.Y());
	double maxX = std::max(std::max(v0.X(), v1.X()), v2.X());
	double maxY = std::max(std::max(v0.Y(), v1.Y()), v2.Y());

	Vector3D p(minX, minY, 0.0);
	int w0Row = Orient(v1, v2, p);
	int w1Row = Orient(v2, v0, p);
	int w2Row = Orient(v0, v1, p);

	int px = p.X();
	int py = p.Y();

	// Rasterize
	for (py = minY; py <= maxY; py++)
	{
		// Barycentric coordinates at start of row
		int w0 = w0Row;
		int w1 = w1Row;
		int w2 = w2Row;

		for (px = minX; px <= maxX; px++)
		{
			// If p is on or inside all edges, render pixel
			if ((w0 | w1 | w2) >= 0)
			{
				// TODO - For future optimisations, I could figure out how to step the perspective
				//        correct barycentric coords (_w0, _w1, _w2) with the none perspective correct
				//        ones (w0, w1, w2).
				//        This would negate the need for the calculations below, saving a small amount
				//        of time per fragment process.
				//        This is important as it might also be able to be extended to step all of the
				//        other attributes too along with it, which will save a lot of time.

				double denom = 1.0 / ((double)w0 + (double)w1 + (double)w2);
				double _w0 = (double)w0 * denom;
				double _w1 = (double)w1 * denom;
				double _w2 = (double)w2 * denom;

				double persCorrector = 1.0 / (_w0 * vertex0.Position.W() + _w1 * vertex1.Position.W() + _w2 * vertex2.Position.W());
				_w0 = _w0 * vertex0.Position.W() * persCorrector;
				_w1 = _w1 * vertex1.Position.W() * persCorrector;
				_w2 = _w2 * vertex2.Position.W() * persCorrector;

				Vector4D fragmentPos(px, py, 0.0, 1.0);
				Vector4D interpPos = (oV0.Position * w0 + oV1.Position * w1 + oV2.Position * w2) * denom;
				Vector4D interpNorm = (vertex0.Normal * _w0 + vertex1.Normal * _w1 + vertex2.Normal * _w2);
				Vector4D interpTex = (vertex0.UVCoord * _w0 + vertex1.UVCoord * _w1 + vertex2.UVCoord * _w2);
				Color interpColor;

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
					interpColor = Color(interpColorVec.X(), interpColorVec.Y(), interpColorVec.Z(), interpColorVec.W());
				}

				if (!RasteringTools::PassesDepthCheck(
						surface,
						Vector3D(
							fragmentPos.X(),
							fragmentPos.Y(),
							interpPos.Z()
						),
						pipelineConfiguration.depthCheckMode
					)
				)
				{
					continue;
				}

				ShaderTools::PixelShader(
					surface,
					camera,
					fragmentPos,
					interpPos,
					interpNorm,
					faceNormal,
					interpColor,
					material,
					lights,
					pipelineConfiguration.depthCheckMode,
					profiler
				);
			}

			// One step to the right
			w0 += A12;
			w1 += A20;
			w2 += A01;
		}

		// One row step
		w0Row += B12;
		w1Row += B20;
		w2Row += B01;
	}
}

double RasteringTools::Orient(
	Vector3D a, 
	Vector3D b, 
	Vector3D c)
{
	Matrix3 m(
		a.X(), b.X(), c.X(),
		a.Y(), b.Y(), c.Y(),
		    1,     1,     1
	);

	return m.Determinant();
}

void RasteringTools::TriangleRasteriser3(
	RenderSurface& surface,
	PipelineConfiguration& pipelineConfiguration,
	Camera& camera,
	Vertex4D& vertex0,
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	Vertex4D& oV0,
	Vertex4D& oV1,
	Vertex4D& oV2,
	Material& material,
	SceneLighting& lights,
	Profiler& profiler)
{
	// Check if face needs culling
	Vector3D vec3_0 = Vector3D(vertex0.Position.X(), vertex0.Position.Y(), vertex0.Position.Z());
	Vector3D vec3_1 = Vector3D(vertex1.Position.X(), vertex1.Position.Y(), vertex1.Position.Z());
	Vector3D vec3_2 = Vector3D(vertex2.Position.X(), vertex2.Position.Y(), vertex2.Position.Z());
	Vector3D v01 = (vec3_1 - vec3_0).Normalised();
	Vector3D v02 = (vec3_2 - vec3_0).Normalised();
	Vector3D cross = v01.Cross(v02).Normalised();

	if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::Clockwise) &&
		cross.Z() < 0.0)
	{
		return;
	}
	else if ((pipelineConfiguration.backFaceCullingMode == BackFaceCullingMode::AntiClockwise) &&
		cross.Z() > 0.0)
	{
		return;
	}

	// Setup some conveinence objects
	Vector2D p0 = Vector2D(vertex0.Position.X(), vertex0.Position.Y());
	Vector2D p1 = Vector2D(vertex1.Position.X(), vertex1.Position.Y());
	Vector2D p2 = Vector2D(vertex2.Position.X(), vertex2.Position.Y());

	Vector3D oVec3_0 = Vector3D(oV0.Position.X(), oV0.Position.Y(), oV0.Position.Z());
	Vector3D oVec3_1 = Vector3D(oV1.Position.X(), oV1.Position.Y(), oV1.Position.Z());
	Vector3D oVec3_2 = Vector3D(oV2.Position.X(), oV2.Position.Y(), oV2.Position.Z());
	Vector3D oV01 = (oVec3_1 - oVec3_0).Normalised();
	Vector3D oV02 = (oVec3_2 - oVec3_0).Normalised();
	Vector3D oCross = oV01.Cross(oV02).Normalised();
	Vector4D faceNormal(oCross.X(), oCross.Y(), oCross.Z(), 1.0);

	Color4D c0d = vertex0.VertColor.GetAs4D();
	Vector4D vc0(c0d.r, c0d.g, c0d.b, c0d.a);
	Color4D c1d = vertex1.VertColor.GetAs4D();
	Vector4D vc1(c1d.r, c1d.g, c1d.b, c1d.a);
	Color4D c2d = vertex2.VertColor.GetAs4D();
	Vector4D vc2(c2d.r, c2d.g, c2d.b, c2d.a);

	bool hasTexture =
		material.GetTexture().Height() > 0 &&
		material.GetTexture().Width() > 0;

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
		InterpolationTools::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p1.X(),
			p1.Y()
		);

	std::vector<int> x12 =
		InterpolationTools::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		InterpolationTools::InterpolateXPixelValues(
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
			Vector3D baryCoords =
				InterpolationTools::FindBaryCentricFactors(
					vertex0.Position,
					vertex1.Position,
					vertex2.Position,
					Vector4D(x, y, 0.0, 1.0)
				);

			double w0 = baryCoords.X();
			double w1 = baryCoords.Y();
			double w2 = baryCoords.Z();

			double denom = 1.0 / ((double)w0 + (double)w1 + (double)w2);
			double _w0 = (double)w0 * denom;
			double _w1 = (double)w1 * denom;
			double _w2 = (double)w2 * denom;

			double persCorrector = 1.0 / (_w0 * vertex0.Position.W() + _w1 * vertex1.Position.W() + _w2 * vertex2.Position.W());
			_w0 = _w0 * vertex0.Position.W() * persCorrector;
			_w1 = _w1 * vertex1.Position.W() * persCorrector;
			_w2 = _w2 * vertex2.Position.W() * persCorrector;

			Vector4D fragmentPos(x, y, 0.0, 1.0);
			Vector4D interpPos = (oV0.Position * w0 + oV1.Position * w1 + oV2.Position * w2) * denom;
			Vector4D interpNorm = (vertex0.Normal * _w0 + vertex1.Normal * _w1 + vertex2.Normal * _w2);
			Vector4D interpTex = (vertex0.UVCoord * _w0 + vertex1.UVCoord * _w1 + vertex2.UVCoord * _w2);
			Color interpColor;

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
				interpColor = Color(interpColorVec.X(), interpColorVec.Y(), interpColorVec.Z(), interpColorVec.W());
			}

			if (!RasteringTools::PassesDepthCheck(
					surface,
					Vector3D(
						fragmentPos.X(),
						fragmentPos.Y(),
						interpPos.Z()
					),
					pipelineConfiguration.depthCheckMode
				)
			)
			{
				continue;
			}

			#pragma omp critical
			ShaderTools::PixelShader(
				surface,
				camera,
				fragmentPos,
				interpPos,
				interpNorm,
				faceNormal,
				interpColor,
				material,
				lights,
				pipelineConfiguration.depthCheckMode,
				profiler
			);
		}
	}
}
