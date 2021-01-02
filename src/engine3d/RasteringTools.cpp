#include "RasteringTools.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Vertex3D.h"
#include "Vertex4D.h"
#include "Color.h"
#include "Texture.h"
#include "Material.h"
#include "Camera.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "ShaderTools.h"
#include "InterpolationTools.h"
#include <cmath>

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
	//vertex.Position.Z(
	//	(((camera.FarClip() - camera.NearClip()) / 2) * vertex.Position.Z()) +
	//	((camera.FarClip() + camera.NearClip()) / 2)
	//);
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
	//vertex.Position.Z(
	//	(((camera.FarClip() - camera.NearClip()) / 2) * vertex.Position.Z()) +
	//	((camera.FarClip() + camera.NearClip()) / 2)
	//);
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

void RasteringTools::TriangleRasteriser(
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

			Vector4D currentPosition(x, y, 0.0, 1.0);
			Color c = Color::Black;

			if (material.GetTexture().Height() > 0 &&
				material.GetTexture().Width() > 0)
			{
				c = InterpolationTools::InterpolateTexture(
					baryCoords,
					oV1,
					oV2,
					oV3,
					currentPosition,
					material.GetTexture(),
					true
				);

				// TODO
				//if (!IsValidSpritePixel(c))
				//{
				//	continue;
				//}
			}
			else
			{
				c = InterpolationTools::InterpolateColor(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					currentPosition,
					true
				);
			}

			Vector4D oPosInterp =
				(oV1.Position * baryCoords.X()) +
				(oV2.Position * baryCoords.Y()) +
				(oV3.Position * baryCoords.Z());

			//double zInterp =
			//	(1 / oV1.Position.Z()) * baryCoords.X() +
			//	(1 / oV2.Position.Z()) * baryCoords.Y() +
			//	(1 / oV3.Position.Z()) * baryCoords.Z();
			//oPosInterp = oPosInterp / zInterp;

			if (!RasteringTools::PassesDepthCheck(
				surface,
				Vector3D(
					currentPosition.X(),
					currentPosition.Y(),
					oPosInterp.Z()  // TODO - Need to find interpolated Z value
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
				InterpolationTools::InterpolateNormal(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					currentPosition,
					true
				),
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
