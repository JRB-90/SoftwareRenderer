#pragma once

#include <cinttypes>

namespace softengine
{
	class Mesh3D;
	class Color;
	class Texture;

	class MeshBuilder
	{
	public:
		MeshBuilder() = delete;

		static Mesh3D BuildCube(
			double width,
			double height,
			double depth,
			Color color
		);

		static Mesh3D BuildCube(
			double width,
			double height,
			double depth,
			Texture& texture
		);

		static Mesh3D BuildCube(
			double width,
			double height,
			double depth,
			Color color,
			Texture& texture
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
	};
}