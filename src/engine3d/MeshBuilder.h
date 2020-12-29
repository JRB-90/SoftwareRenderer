#pragma once

#include <cinttypes>

namespace softengine
{
	class Mesh3D;
	class Color;
	class Texture;
	class Frame3D;
	class Material;

	class MeshBuilder
	{
	public:
		MeshBuilder() = delete;

		static Mesh3D BuildCube(
			double width,
			double height,
			double depth,
			Material& material
		);

		static Mesh3D BuildCube(
			double width,
			double height,
			double depth,
			Color colorFTL,
			Color colorFTR,
			Color colorFBL,
			Color colorFBR,
			Color colorBTL,
			Color colorBTR,
			Color colorBBL,
			Color colorBBR
		);

		static Mesh3D BuildFrame(
			double size
		);

		static Mesh3D BuildFrame(
			double size,
			Frame3D transform
		);
	};
}