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
#include "Material.h"
#include "RasteringTools.h"
#include "InterpolationTools.h"
#include "ShadingType.h"
#include "SceneLighting.h"
#include "ShaderTools.h"
#include "Profiler.h"

#include <iostream>
#include <cmath>
#include <omp.h>

using namespace softengine;

RenderPipeline3D::RenderPipeline3D(
	PipelineConfiguration pipelineConfiguration)
  :
	pipelineConfiguration(pipelineConfiguration)
{
}

void RenderPipeline3D::Run(
	RenderSurface& surface,
	DrawType drawType,
	VBO3D& vbo, 
	Matrix4& model,
	Camera& camera,
	Material& material,
	SceneLighting& lights)
{
	if (pipelineConfiguration.wireframeModeEnabled)
	{
		RunLines(
			surface,
			vbo,
			model,
			camera,
			lights
		);

		return;
	}

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
			material,
			lights
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
	Profiler pipelineProfiler;

	for (size_t i = 0; i < vbo.IndicesSize(); i++)
	{
		pipelineProfiler.ResetTimer();

		Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

		Vertex4D vert = 
			ShaderTools::SimpleVertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				MVP
			);

		//VertexShaderIn vertIn(
		//	&surface,
		//	&vbo.Vertices(vbo.Indices(i)),
		//	&model,
		//	&camera
		//);
		//VertexShaderOut vertOut;
		//ShaderTools::SimpleVertexShader(vertIn, vertOut);

		pipelineProfiler.AddTiming("Vertex Shader");

		if (!RasteringTools::PassesClipTest(vert))
		{
			continue;
		}

		//if (RasteringTools::PassesClipTest(vertOut))
		//{
		//	continue;
		//}

		pipelineProfiler.AddTiming("Clip Test");

		RasteringTools::TranformToRasterSpace(
			vert,
			camera
		);

		//RasteringTools::TranformToRasterSpace(
		//	vertOut,
		//	camera
		//);

		pipelineProfiler.AddTiming("Raster Space");

		RasteringTools::PointRasteriser(
			surface,
			pipelineConfiguration,
			camera,
			vert,
			lights
		);

		//Vertex4D oV1(
		//	vbo.Vertices(vbo.Indices(i)).Position
		//);
		//PointRasteriserIn rastIn(
		//	&surface,
		//	&pipelineConfiguration,
		//	&camera,
		//	&Material(),
		//	&lights,
		//	&vertOut.vertex,
		//	&oV1
		//);
		//RasteringTools::PointRasteriser(rastIn);

		pipelineProfiler.AddTiming("Point Raster");
	}

	pipelineProfiler.PrintTimings();
}

void RenderPipeline3D::RunLines(
	RenderSurface& surface, 
	VBO3D& vbo, 
	Matrix4& model, 
	Camera& camera,
	SceneLighting& lights)
{
	Profiler pipelineProfiler;

	for (size_t i = 0; i < vbo.IndicesSize() - 1; i += 2)
	{
		pipelineProfiler.ResetTimer();

		Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

		Vertex4D vert1 =
			ShaderTools::SimpleVertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i)),
				MVP
			);
		Vertex4D vert2 =
			ShaderTools::SimpleVertexShader(
				surface,
				vbo.Vertices(vbo.Indices(i + 1)),
				MVP
			);

		pipelineProfiler.AddTiming("Vertex Shader");

		if (!RasteringTools::PassesClipTest(vert1) &&
			!RasteringTools::PassesClipTest(vert2))
		{
			continue;
		}

		pipelineProfiler.AddTiming("Clip Test");

		RasteringTools::TranformToRasterSpace(
			vert1,
			camera
		);

		RasteringTools::TranformToRasterSpace(
			vert2,
			camera
		);

		pipelineProfiler.AddTiming("Raster Space");

		RasteringTools::LineRasteriser(
			surface,
			pipelineConfiguration,
			camera,
			vert1,
			vert2,
			lights
		);

		pipelineProfiler.AddTiming("Line Raster");
	}

	pipelineProfiler.PrintTimings();
}

void RenderPipeline3D::RunTriangles(
	RenderSurface& surface,
	VBO3D& vbo,
	Matrix4& model, 
	Camera& camera,
	Material& material,
	SceneLighting& lights)
{
	Profiler pipelineProfiler;

	Matrix4 MVP = camera.ProjectionMatrix() * camera.ViewMatrix() * model;

	#pragma omp parallel num_threads(2) default(none) shared(surface, vbo, MVP, camera, material, lights)
	{
		//#pragma omp single
		{
			#pragma omp for schedule(runtime)
			for (int i = 0; i < vbo.IndicesSize() - 2; i += 3)
			{
				RunTriangle(
					surface,
					vbo,
					i,
					MVP,
					camera,
					material,
					lights
				);
			}
		}
	}

	pipelineProfiler.AddTiming("Model Total");
	pipelineProfiler.PrintTimings();
}

void RenderPipeline3D::RunTriangle(
	RenderSurface& surface, 
	VBO3D& vbo,
	int& index,
	Matrix4& mvp, 
	Camera& camera, 
	Material& material, 
	SceneLighting& lights)
{
	Vertex4D vert1 =
		ShaderTools::SimpleVertexShader(
			surface,
			vbo.Vertices(vbo.Indices(index)),
			mvp
		);
	Vertex4D vert2 =
		ShaderTools::SimpleVertexShader(
			surface,
			vbo.Vertices(vbo.Indices(index + 1)),
			mvp
		);
	Vertex4D vert3 =
		ShaderTools::SimpleVertexShader(
			surface,
			vbo.Vertices(vbo.Indices(index + 2)),
			mvp
		);

	if (RasteringTools::PassesClipTest(vert1) &&
		RasteringTools::PassesClipTest(vert2) &&
		RasteringTools::PassesClipTest(vert3))
	{
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

		std::vector<RasterFragment> fragments =
			RasteringTools::TriangleRasteriser(
				pipelineConfiguration,
				vert1,
				vert2,
				vert3,
				screenSpaceV1,
				screenSpaceV2,
				screenSpaceV3
			);

		Vector4D vc1 = vert1.VertColor.ToVec4();
		Vector4D vc2 = vert1.VertColor.ToVec4();
		Vector4D vc3 = vert1.VertColor.ToVec4();

		Vector4D faceNormal =
			InterpolationTools::CalculateFaceNormal(
				screenSpaceV1.Position,
				screenSpaceV2.Position,
				screenSpaceV3.Position
			);

		for (int i = 0; i < fragments.size(); i++)
		{
			InterpolatedFragment interpolatedFragment =
				InterpolationTools::InterpolateFragment(
					fragments[i],
					vert1,
					vert2,
					vert3,
					screenSpaceV1,
					screenSpaceV2,
					screenSpaceV3,
					vc1,
					vc2,
					vc3,
					material
				);

			if (RasteringTools::PassesDepthCheck(
				surface,
				Vector3D(
					fragments[i].Fragment.X(),
					fragments[i].Fragment.Y(),
					interpolatedFragment.Position.Z()
				),
				pipelineConfiguration.depthCheckMode
			)
				)
			{
				ShaderTools::PixelShader(
					surface,
					camera,
					interpolatedFragment.Fragment,
					interpolatedFragment.Position,
					interpolatedFragment.Normal,
					faceNormal,
					interpolatedFragment.FragColor,
					material,
					lights,
					pipelineConfiguration.depthCheckMode
				);
			}
		}
	}
}
