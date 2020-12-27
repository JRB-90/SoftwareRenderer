#include "RenderPipeline3D.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "VBO3D.h"
#include "Vector3D.h"
#include "Vertex3D.h"
#include "Vector4D.h"
#include "Vertex4D.h"
#include "Matrix4.h"
#include "Camera.h"
#include "Color.h"
#include "Texture.h"
#include "RasteringTools.h"
#include "ShadingType.h"
#include "SceneLighting.h"

#include <iostream>
#include <cmath>

using namespace softengine;

RenderPipeline3D::RenderPipeline3D(
	bool isWireFrame,
	DrawType drawType,
	BackFaceCullingMode cullingMode, 
	DepthCheckMode depthCheckMode)
  :
	isWireFrame(isWireFrame),
	drawType(drawType),
	cullingMode(cullingMode),
	depthCheckMode(depthCheckMode)
{
}

void RenderPipeline3D::Run(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model,
	Camera& camera,
	Texture& texture,
	SceneLighting& lights,
	ShadingType shadingType)
{
	switch (drawType)
	{
	case DrawType::Points:
		RunPoints(
			surface,
			vbo,
			model,
			camera,
			lights
		);
		break;
	case DrawType::Lines:
		RunLines(
			surface,
			vbo,
			model,
			camera,
			lights
		);
		break;
	case DrawType::Triangles:
		RunTriangles(
			surface,
			vbo,
			model,
			camera,
			texture,
			lights,
			shadingType
		);
		break;
	case DrawType::Quads:
		RunQuads(
			surface,
			vbo,
			model,
			camera,
			texture,
			lights,
			shadingType
		);
		break;
	default:
		return;
	}
}

void RenderPipeline3D::RunPoints(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	SceneLighting& lights)
{
	for (size_t i = 0; i < vbo.IndicesSize(); i++)
	{
		Vertex4D vert = 
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);

		if (RasteringTools::PassesClipTest(vert))
		{
			continue;
		}

		RasteringTools::TranformToRasterSpace(
			vert,
			camera
		);

		PointRasteriser(
			surface,
			vert,
			lights
		);
	}
}

void RenderPipeline3D::RunLines(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	SceneLighting& lights)
{
	for (size_t i = 0; i < vbo.IndicesSize() - 1; i += 2)
	{
		Vertex4D vert1 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);
		Vertex4D vert2 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 1)),
				model,
				camera
			);

		if (!RasteringTools::PassesClipTest(vert1) &&
			!RasteringTools::PassesClipTest(vert2))
		{
			continue;
		}

		RasteringTools::TranformToRasterSpace(
			vert1,
			camera
		);

		RasteringTools::TranformToRasterSpace(
			vert2,
			camera
		);

		LineRasteriser(
			surface,
			vert1,
			vert2,
			lights
		);
	}
}

void RenderPipeline3D::RunTriangles(
	RenderSurface& surface,
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Texture& texture,
	SceneLighting& lights,
	ShadingType shadingType)
{
	for (size_t i = 0; i < vbo.IndicesSize() - 2; i += 3)
	{
		Vertex4D vert1 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);
		Vertex4D vert2 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 1)),
				model,
				camera
			);
		Vertex4D vert3 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 2)),
				model,
				camera
			);

		if (!RasteringTools::PassesClipTest(vert1) &&
			!RasteringTools::PassesClipTest(vert2) &&
			!RasteringTools::PassesClipTest(vert3))
		{
			continue;
		}

		Vertex4D screenSpaceV1(vert1);
		Vertex4D screenSpaceV2(vert2);
		Vertex4D screenSpaceV3(vert3);

		RasteringTools::TranformToRasterSpace(
			vert1,
			camera
		);
		RasteringTools::TranformToRasterSpace(
			vert2,
			camera
		);
		RasteringTools::TranformToRasterSpace(
			vert3,
			camera
		);

		TriangleRasteriser(
			surface,
			vert1,
			vert2,
			vert3,
			screenSpaceV1,
			screenSpaceV2,
			screenSpaceV3,
			texture,
			lights,
			shadingType
		);
	}
}

void RenderPipeline3D::RunQuads(
	RenderSurface& surface, 
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Texture& texture,
	SceneLighting& lights,
	ShadingType shadingType)
{
	// TODO
}

Vertex4D RenderPipeline3D::VertexShader(
	RenderSurface& surface, 
	Vertex3D& vertex,
	Matrix4& model, 
	Camera& camera)
{
	Vector4D vert(
		vertex.Position.X(),
		vertex.Position.Y(),
		vertex.Position.Z(),
		1.0
	);

	// Transform into world coordinates
	vert = vert * model;
	// Transform to camera space
	vert = vert * camera.ViewMatrix();
	// Project point into camera plane
	vert = vert * camera.ProjectionMatrix();

	return
		Vertex4D(
			vert,
			Vector4D(
				vertex.UVCoord.X(),
				vertex.UVCoord.Y(),
				0.0,
				1.0
			),
			Vector4D(
				vertex.Normal.X(),
				vertex.Normal.Y(),
				vertex.Normal.Z(),
				1.0
			),
			vertex.VertColor
		);
}

void RenderPipeline3D::PointRasteriser(
	RenderSurface& surface, 
	Vertex4D& vertex,
	SceneLighting& lights)
{
	PixelShader(
		surface,
		vertex.Position,
		vertex.Normal,
		vertex.VertColor,
		Vector4D(),
		lights,
		ShadingType::None
	);
}

void RenderPipeline3D::LineRasteriser(
	RenderSurface& surface, 
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	SceneLighting& lights)
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

		PixelShader(
			surface,
			Vector4D(x, y, z, 1.0), // TODO - Should this be 1??
			vertex1.Normal, //TODO - Interpolate normal
			Color::InterpolateColor(
				vertex1.VertColor,
				vertex2.VertColor,
				factor
			),
			Vector4D(),
			lights,
			ShadingType::None
		);
	}
}

void RenderPipeline3D::TriangleRasteriser(
	RenderSurface& surface, 
	Vertex4D& vertex1,
	Vertex4D& vertex2,
	Vertex4D& vertex3,
	Vertex4D& oV1,
	Vertex4D& oV2,
	Vertex4D& oV3,
	Texture& texture,
	SceneLighting& lights,
	ShadingType shadingType)
{
	Vector3D vec3_1 = Vector3D(vertex1.Position.X(), vertex1.Position.Y(), vertex1.Position.Z());
	Vector3D vec3_2 = Vector3D(vertex2.Position.X(), vertex2.Position.Y(), vertex2.Position.Z());
	Vector3D vec3_3 = Vector3D(vertex3.Position.X(), vertex3.Position.Y(), vertex3.Position.Z());
	Vector3D v12 = (vec3_2 - vec3_1).Normalised();
	Vector3D v13 = (vec3_3 - vec3_1).Normalised();
	Vector3D cross = v12.Cross(v13).Normalised();

	if ((cullingMode == BackFaceCullingMode::Clockwise) &&
		cross.Z() < 0.0)
	{
		return;
	}
	else if ((cullingMode == BackFaceCullingMode::AntiClockwise) &&
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
		RasteringTools::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p1.X(),
			p1.Y()
		);

	std::vector<int> x12 =
		RasteringTools::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		RasteringTools::InterpolateXPixelValues(
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
				RasteringTools::FindBaryCentricFactors(
					vertex1.Position,
					vertex2.Position,
					vertex3.Position,
					Vector4D(x, y, 0.0, 1.0)
				);

		    Vector4D currentPosition(x, y, 0.0, 1.0);
			Color c = Color::Black;

			if (texture.Height() > 0 &&
				texture.Width() > 0)
			{
				c = RasteringTools::InterpolateTexture(
					baryCoords,
					oV1,
					oV2,
					oV3,
					currentPosition,
					texture,
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
				c = RasteringTools::InterpolateColor(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					currentPosition,
					true
				);
			}

			PixelShader(
				surface,
				currentPosition,
				RasteringTools::InterpolateNormal(
					baryCoords,
					vertex1,
					vertex2,
					vertex3,
					currentPosition,
					true
				),
				c,
				Vector4D(), // TODO - Figure out flat normal here
				lights,
				shadingType
			);
		}
	}
}

void RenderPipeline3D::PixelShader(
	RenderSurface& surface,
	Vector4D& fragment,
	Vector4D& normal,
	Color& color,
	Vector4D& faceNormal,
	SceneLighting& lights,
	ShadingType shadingType)
{
	if (!RasteringTools::PassesDepthCheck(
			surface,
			fragment,
			depthCheckMode)
	)
	{
		return;
	}

	switch (shadingType)
	{
	case ShadingType::None:
		surface.SetPixelValue(
			fragment.X(),
			fragment.Y(),
			color
		);
		break;
	case ShadingType::Flat:
		PixelShaderFlat(
			surface,
			fragment,
			normal,
			color,
			faceNormal,
			lights
		);
		break;
	case ShadingType::Phong:
		PixelShaderPhong(
			surface,
			fragment,
			normal,
			color,
			lights
		);
		break;
	default:
		break;
	}
}

void RenderPipeline3D::PixelShaderFlat(
	RenderSurface& surface, 
	Vector4D& fragment, 
	Vector4D& normal, 
	Color& color, 
	Vector4D& faceNormal, 
	SceneLighting& lights)
{
	Color ambientLight = lights.GetAmbientLight().GetColor() * lights.GetAmbientLight().Strength();
	Vector3D flatNormal = Vector3D(faceNormal.X(), faceNormal.Y(), faceNormal.Z()).Normalised();
	Vector3D lightDir = lights.GetDirectionalLights()[0].Direction().Normalised() * -1.0;

	double intensity = 
		std::max(
			flatNormal.Dot(lightDir), 
			0.0
		);

	//std::cout << intensity << std::endl;

	Color diffuseLight = lights.GetDirectionalLights()[0].GetColor() * intensity;
	Color ambient = color * ambientLight;
	Color diffuse = color * diffuseLight;

	//surface.SetPixelValue(
	//	fragment.X(),
	//	fragment.Y(),
	//	diffuse
	//);

	surface.SetPixelValue(
		fragment.X(),
		fragment.Y(),
		Color(
			normal.X(),
			normal.Y(),
			normal.Z(),
			1.0
		)
	);
}

void RenderPipeline3D::PixelShaderPhong(
	RenderSurface& surface, 
	Vector4D& fragment, 
	Vector4D& normal, 
	Color& color, 
	SceneLighting& lights)
{
}
