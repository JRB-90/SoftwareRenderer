#include "AssimpImporter.h"

#include "Mesh3D.h"
#include "Material.h"
#include "Vertex3D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Color.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>
#include <vector>

using namespace softengine;

Mesh3D AssimpImporter::LoadMesh(
	const std::string& path,
	Material& material,
	bool flipVertexOrder,
	bool flipNormals)
{
	Assimp::Importer importer;
	const aiScene* scene = 
		importer.ReadFile(
			path,
			aiProcess_Triangulate | aiProcess_FlipWindingOrder
		);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::runtime_error(importer.GetErrorString());
	}

	if (!scene->HasMeshes())
	{
		throw std::runtime_error("No meshes found in file");
	}

	std::vector<Vertex3D> vertices;
	std::vector<size_t> indices;
	aiMesh* mesh = scene->mMeshes[0];

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D position = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];

		Vector2D texCoords;
		if (mesh->mTextureCoords[0])
		{
			texCoords.X(mesh->mTextureCoords[0][i].x);
			texCoords.Y(mesh->mTextureCoords[0][i].y);
		}

		vertices.push_back(
			Vertex3D(
				Vector3D(position.x, position.y, position.z),
				texCoords,
				Vector3D(normal.x, normal.y, normal.z)
			)
		);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return
		Mesh3D(
			indices,
			vertices,
			material
		);
}
