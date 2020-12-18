#pragma once

#include "IScene.h"
#include "Mesh3D.h"
#include <vector>

namespace softengine
{
	class Scene3D : public IScene
	{
	public:
		Scene3D();

		void ClearAll() override;

		std::vector<Mesh3D>& Meshes() { return meshes; }

	private:
		std::vector<Mesh3D> meshes;
	};
}