#include "MeshBuilder.h"

#include "Mesh3D.h"
#include "Color.h"
#include "Texture.h"
#include "Frame3D.h"
#include "Material.h"

using namespace softengine;

Mesh3D MeshBuilder::BuildCube(
	double width, 
	double height, 
	double depth, 
	Material& material,
	bool wrappedTexCoords)
{
	std::vector<size_t> indicesSq =
	{
		// Front Face
		0, 1, 3, 1, 2, 3,

		// Back Face
		4, 5, 7, 5, 6, 7,

		// Left Face
		8, 9, 11, 9, 10, 11,

		// Right Face
		12, 13, 15, 13, 14, 15,

		// Bottom Face
		16, 17, 19, 17, 18, 19,

		// Top Face
		20, 21, 23, 21, 22, 23,
	};

	double halfWidth = width / 2.0;
	double halfHeight = height / 2.0;
	double halfDepth = depth / 2.0;

	std::vector<Vertex3D> verticesSq;

	if (wrappedTexCoords)
	{
		verticesSq =
		{
			// Front Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.26, 0.34), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// F_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.49, 0.34), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// F_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.49, 0.65), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// F_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.26, 0.65), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),	// F_BL

			// Back Verts
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.76, 0.34), Vector3D(1, 1, -1).Normalised(), material.Difffuse()),		// B_TL
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.99, 0.34), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),	// B_TR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.99, 0.65), Vector3D(-1, -1, -1).Normalised(), material.Difffuse()),	// B_BR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.76, 0.65), Vector3D(1, -1, -1).Normalised(), material.Difffuse()),	// B_BL

			// Left Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.01, 0.34), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),	// L_TL
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.24, 0.34), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// L_TR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.24, 0.65), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),	// L_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.01, 0.65), Vector3D(-1, -1, -1).Normalised(), material.Difffuse()),	// L_BL

			// Right Verts
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.51, 0.34), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// R_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.74, 0.34), Vector3D(1, 1, -1).Normalised(), material.Difffuse()),		// R_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.74, 0.65), Vector3D(1, -1, -1).Normalised(), material.Difffuse()),	// R_BR
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.51, 0.65), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// R_BL

			// Bottom Verts
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.26, 0.67), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),	// Bo_TL
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.49, 0.67), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// Bo_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.49, 0.99), Vector3D(1, -1, 0).Normalised(), material.Difffuse()),		// Bo_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.26, 0.99), Vector3D(-1, -1, 0).Normalised(), material.Difffuse()),	// Bo_BL

			// Top Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.26, 0.01), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),	// B_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.49, 0.01), Vector3D(1, 1, -1).Normalised(), material.Difffuse()),		// B_TR
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.49, 0.32), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// T_BR
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.26, 0.32), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// T_BL
		};
	}
	else
	{
		verticesSq =
		{
			// Front Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.01, 0.01), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// F_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.99, 0.01), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// F_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.99, 0.99), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// F_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.01, 0.99), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),		// F_BL

			// Back Verts
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.01, 0.01), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),		// B_TL
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.99, 0.01), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// B_TR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.99, 0.99), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),	// B_BR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.01, 0.99), Vector3D(-1, -1, -1).Normalised(), material.Difffuse()),		// B_BL

			// Left Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.01, 0.01), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),		// L_TL
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.99, 0.01), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// L_TR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.99, 0.99), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),		// L_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.01, 0.99), Vector3D(-1, -1, -1).Normalised(), material.Difffuse()),	// L_BL

			// Right Verts
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.01, 0.01), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// R_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.99, 0.01), Vector3D(1, 1, -1).Normalised(), material.Difffuse()),		// R_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.99, 0.99), Vector3D(1, -1, -1).Normalised(), material.Difffuse()),		// R_BR
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.01, 0.99), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// R_BL

			// Bottom Verts
			Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.01, 0.01), Vector3D(-1, -1, 1).Normalised(), material.Difffuse()),		// Bo_TL
			Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.99, 0.01), Vector3D(1, -1, 1).Normalised(), material.Difffuse()),		// Bo_TR
			Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.99, 0.99), Vector3D(1, -1, 0).Normalised(), material.Difffuse()),		// Bo_BR
			Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.01, 0.99), Vector3D(-1, -1, 0).Normalised(), material.Difffuse()),	// Bo_BL

			// Top Verts
			Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.01, 0.01), Vector3D(-1, 1, -1).Normalised(), material.Difffuse()),		// B_TL
			Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.99, 0.01), Vector3D(1, 1, -1).Normalised(), material.Difffuse()),		// B_TR
			Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.99, 0.99), Vector3D(1, 1, 1).Normalised(), material.Difffuse()),		// T_BR
			Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.01, 0.99), Vector3D(-1, 1, 1).Normalised(), material.Difffuse()),		// T_BL
		};
	}

	return
		Mesh3D(
			indicesSq,
			verticesSq,
			Frame3D(
				Vector3D(0, 0, 1.0),
				Rotation3D()
			),
			DrawType::Triangles,
			material
		);
}

Mesh3D MeshBuilder::BuildCube(
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
	Color colorBBR)
{
	std::vector<size_t> indicesSq =
	{
		// Front Face
		0, 1, 2, 1, 3, 2,

		// Back Face
		5, 4, 6, 6, 7, 5,

		// Left Face
		4, 0, 2, 2, 6, 4,

		// Right Face
		1, 5, 7, 7, 3, 1,

		// Bottom Face
		7, 2, 3, 7, 6, 2,

		// Top Face
		4, 5, 1, 1, 0, 4,
	};

	double halfWidth = width / 2.0;
	double halfHeight = height / 2.0;
	double halfDepth = depth / 2.0;

	std::vector<Vertex3D> verticesSq =
	{
		// Front Verts
		Vertex3D(Vector3D(-halfWidth, -halfHeight, halfDepth), Vector2D(0.26, 0.34), colorFTL),  // F_TL 0
		Vertex3D(Vector3D(halfWidth, -halfHeight, halfDepth), Vector2D(0.49, 0.34), colorFTR),   // F_TR 1
		Vertex3D(Vector3D(-halfWidth, halfHeight, halfDepth), Vector2D(0.26, 0.65), colorFBR),   // F_BL 2
		Vertex3D(Vector3D(halfWidth, halfHeight, halfDepth), Vector2D(0.49, 0.65), colorFBL),    // F_BR 3

		// Back Verts
		Vertex3D(Vector3D(-halfWidth, -halfHeight, -halfDepth), Vector2D(0.99, 0.34), colorBTR),  // B_TR 4
		Vertex3D(Vector3D(halfWidth, -halfHeight, -halfDepth), Vector2D(0.76, 0.34), colorBTL),   // B_TL 5
		Vertex3D(Vector3D(-halfWidth, halfHeight, -halfDepth), Vector2D(0.99, 0.65), colorBBR),   // B_BR 6
		Vertex3D(Vector3D(halfWidth, halfHeight, -halfDepth), Vector2D(0.76, 0.65), colorBBL),    // B_BL 7
	};

	return
		Mesh3D(
			indicesSq,
			verticesSq,
			Frame3D(
				Vector3D(0, 0, 1.0),
				Rotation3D()
			),
			DrawType::Triangles
		);
}

Mesh3D MeshBuilder::BuildFrame(double size)
{
	std::vector<size_t> indices = { 0, 1, 2, 3, 4, 5 };

	std::vector<Vertex3D> vertices =
	{
		Vertex3D(Vector3D(0, 0, 0), Color::Red),		// X Origin
		Vertex3D(Vector3D(size, 0, 0), Color::Red),		// X Axis
		Vertex3D(Vector3D(0, 0, 0), Color::Green),		// Y Origin
		Vertex3D(Vector3D(0, size, 0), Color::Green),	// Y Axis
		Vertex3D(Vector3D(0, 0, 0), Color::Blue),		// Z Origin
		Vertex3D(Vector3D(0, 0, size), Color::Blue),	// Z Axis
	};

	return
		Mesh3D(
			indices,
			vertices,
			Frame3D(),
			DrawType::Lines
		);
}

Mesh3D MeshBuilder::BuildFrame(
	double size,
	Frame3D transform)
{
	std::vector<size_t> indices =
	{
		0, 1, 2, 3, 4, 5,
		//6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 6
	};

	std::vector<Vertex3D> vertices =
	{
		Vertex3D(Vector3D(0, 0, 0), Color::Red),		// X Origin
		Vertex3D(Vector3D(size, 0, 0), Color::Red),		// X Axis
		Vertex3D(Vector3D(0, 0, 0), Color::Green),		// Y Origin
		Vertex3D(Vector3D(0, size, 0), Color::Green),	// Y Axis
		Vertex3D(Vector3D(0, 0, 0), Color::Blue),		// Z Origin
		Vertex3D(Vector3D(0, 0, size), Color::Blue),	// Z Axis

		Vertex3D(Vector3D(size / 5, size / 5, 0), Color::White),
		Vertex3D(Vector3D(size / 5, 0, 0), Color::White),
		Vertex3D(Vector3D(size / 5, 0, size / 5), Color::White),
		Vertex3D(Vector3D(0, 0, size / 5), Color::White),
		Vertex3D(Vector3D(0, size / 5, size / 5), Color::White),
		Vertex3D(Vector3D(0, size / 5, 0), Color::White),
	};

	return
		Mesh3D(
			indices,
			vertices,
			transform,
			DrawType::Lines
		);
}
