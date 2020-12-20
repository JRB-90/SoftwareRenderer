#include "RenderPipeline3D.h"
#include "RenderSurface.h"
#include "PipelineConfiguration3D.h"
#include "VBO3D.h"
#include "Vector3D.h"
#include "Vertex3D.h"
#include "Vector4D.h"
#include "Matrix4.h"
#include "Camera.h"
#include "Color.h"
#include "Texture.h"
#include "RasteringTools.h"

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
	Texture& texture)
{
	switch (drawType)
	{
	case DrawType::Points:
		RunPoints(
			surface,
			vbo,
			model,
			camera
		);
		break;
	case DrawType::Lines:
		RunLines(
			surface,
			vbo,
			model,
			camera
		);
		break;
	case DrawType::Triangles:
		RunTriangles(
			surface,
			vbo,
			model,
			camera,
			texture
		);
		break;
	case DrawType::Quads:
		RunQuads(
			surface,
			vbo,
			model,
			camera,
			texture
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
	Camera& camera)
{
	for (size_t i = 0; i < vbo.IndicesSize(); i++)
	{
		// TODO - Make a Vertex4D object to store the homogenous space position + normal
		Vector4D vert = 
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);

		if (PassesClipTest(vert))
		{
			PointRasteriser(
				surface,
				Vertex3D(
					TranformToRasterSpace(
						vert,
						camera
					),
					vbo.Vertices(vbo.Indices(i)).UVCoord,
					vbo.Vertices(vbo.Indices(i)).Normal,
					vbo.Vertices(vbo.Indices(i)).VertColor
				)
			);
		}
	}
}

void RenderPipeline3D::RunLines(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera)
{
	for (size_t i = 0; i < vbo.IndicesSize() - 1; i += 2)
	{
		Vector4D vert1 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);
		Vector4D vert2 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 1)),
				model,
				camera
			);

		if (PassesClipTest(vert1) &&
			PassesClipTest(vert2))
		{
			LineRasteriser(
				surface,
				Vertex3D(
					TranformToRasterSpace(
						vert1,
						camera
					),
					vbo.Vertices(vbo.Indices(i)).UVCoord,
					vbo.Vertices(vbo.Indices(i)).Normal,
					vbo.Vertices(vbo.Indices(i)).VertColor
				),
				Vertex3D(
					TranformToRasterSpace(
						vert2,
						camera
					),
					vbo.Vertices(vbo.Indices(i + 1)).UVCoord,
					vbo.Vertices(vbo.Indices(i + 1)).Normal,
					vbo.Vertices(vbo.Indices(i + 1)).VertColor
				)
			);
		}
	}
}

void RenderPipeline3D::RunTriangles(
	RenderSurface& surface,
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	Texture& texture)
{
	for (size_t i = 0; i < vbo.IndicesSize() - 2; i += 3)
	{
		Vector4D vert1 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				model,
				camera
			);
		Vector4D vert2 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 1)),
				model,
				camera
			);
		Vector4D vert3 =
			VertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 2)),
				model,
				camera
			);

		if (PassesClipTest(vert1) &&
			PassesClipTest(vert2) &&
			PassesClipTest(vert3))
		{
			TriangleRasteriser(
				surface,
				Vertex3D(
					TranformToRasterSpace(
						vert1,
						camera
					),
					vbo.Vertices(vbo.Indices(i)).UVCoord,
					vbo.Vertices(vbo.Indices(i)).Normal,
					vbo.Vertices(vbo.Indices(i)).VertColor
				),
				Vertex3D(
					TranformToRasterSpace(
						vert2,
						camera
					),
					vbo.Vertices(vbo.Indices(i + 1)).UVCoord,
					vbo.Vertices(vbo.Indices(i + 1)).Normal,
					vbo.Vertices(vbo.Indices(i + 1)).VertColor
				),
				Vertex3D(
					TranformToRasterSpace(
						vert3,
						camera
					),
					vbo.Vertices(vbo.Indices(i + 2)).UVCoord,
					vbo.Vertices(vbo.Indices(i + 2)).Normal,
					vbo.Vertices(vbo.Indices(i + 2)).VertColor
				),
				texture
			);
		}
	}
}

void RenderPipeline3D::RunQuads(
	RenderSurface& surface, 
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Texture& texture)
{
	// TODO
}

Vector4D RenderPipeline3D::VertexShader(
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

	return vert;
}

bool RenderPipeline3D::PassesClipTest(Vector4D& v1)
{
	return true;

	// TODO - Need to investigate this a little more as it seems to be clipping too early

	return
		-v1.W() <= v1.X() &&
		v1.X() <= v1.W() &&
		-v1.W() <= v1.Y() &&
		v1.Y() <= v1.W() &&
		-v1.W() <= v1.Z() &&
		v1.Z() <= v1.W();
}

Vector3D RenderPipeline3D::TranformToRasterSpace(
	Vector4D& vertex,
	Camera& camera)
{
	// Perspective divide
	Vector3D vert(
		vertex.X() / vertex.W(),
		vertex.Y() / vertex.W(),
		vertex.Z() / vertex.W()
	);

	// Viewport transform
	vert.X((vert.X() + 1.0) * 0.5 * (camera.Width() - 1));
	vert.Y((vert.Y() + 1.0) * 0.5 * (camera.Height() - 1));

	return vert;
}

void RenderPipeline3D::PointRasteriser(
	RenderSurface& surface, 
	Vertex3D& vertex)
{
	PixelShader(
		surface,
		vertex.Position,
		vertex.Normal,
		vertex.VertColor
	);
}

void RenderPipeline3D::LineRasteriser(
	RenderSurface& surface, 
	Vertex3D& vertex1,
	Vertex3D& vertex2)
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
			Vector3D(x, y, z),
			vertex1.Normal, //TODO - Interpolate normal
			Color::InterpolateColor(
				vertex1.VertColor,
				vertex2.VertColor,
				factor
			)
		);
	}
}

void RenderPipeline3D::TriangleRasteriser(
	RenderSurface& surface, 
	Vertex3D& vertex1,
	Vertex3D& vertex2,
	Vertex3D& vertex3,
	Texture& texture)
{
	Vector3D v12 = (vertex2.Position - vertex1.Position).Normalised();
	Vector3D v13 = (vertex3.Position - vertex1.Position).Normalised();
	Vector3D cross = v12.Cross(v13);

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
				RasteringTools::FindBaryCentricCoords(
					vertex1,
					vertex2,
					vertex3,
					Vector2D(x, y)
				);

			double z = 
				vertex1.Position.Z() * baryCoords.X() + 
				vertex2.Position.Z() * baryCoords.Y() +
				vertex3.Position.Z() * baryCoords.Z();
			Vector3D cur(x, y, z);
			Color c = Color::Black;

			if (texture.Height() > 0 &&
				texture.Width() > 0)
			{
				c = RasteringTools::InterpolateTexture(
					vertex1,
					vertex2,
					vertex3,
					cur,
					texture
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
					vertex1,
					vertex2,
					vertex3,
					cur
				);
			}

			PixelShader(
				surface,
				cur,
				vertex1.Normal, // TODO - Interpolate normal
				c
			);
		}
	}
}

void RenderPipeline3D::PixelShader(
	RenderSurface& surface,
	Vector3D& fragment,
	Vector3D& normal,
	Color& color)
{
	switch (depthCheckMode)
	{
	case DepthCheckMode::NoDepthCheck:
		surface.SetPixelValue(
			fragment.X(),
			fragment.Y(),
			color
		);
		break;
	case DepthCheckMode::DepthCheckGreaterThan:
		if (
			surface.PassesZCheck(
				fragment.X(),
				fragment.Y(),
				fragment.Z()
			)
		)
		{
			surface.SetPixelValue(
				fragment.X(),
				fragment.Y(),
				color
			);
		}
		break;
	case DepthCheckMode::DepthCheckLessThan:
		if (
			!surface.PassesZCheck(
				fragment.X(),
				fragment.Y(),
				fragment.Z()
			)
		)
		{
			surface.SetPixelValue(
				fragment.X(),
				fragment.Y(),
				color
			);
		}
		break;
	default:
		break;
	}
}
