#pragma once

#include "IScene.h"
#include "Mesh3D.h"
#include "SceneLighting.h"
#include <vector>
#include <memory>

namespace softengine
{
	class Scene3D : public IScene
	{
	public:
		Scene3D();

		void ClearAll() override;

		std::vector<Mesh3D>& Meshes() { return meshes; }
		SceneLighting& Lighting() { return lighting; }

	private:
		std::vector<Mesh3D> meshes;
		SceneLighting lighting;
	};
}