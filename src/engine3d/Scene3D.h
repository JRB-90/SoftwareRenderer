#pragma once

#include "IScene.h"
#include "Mesh3D.h"
#include "Light.h"
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
		std::vector<std::shared_ptr<Light>>& Lights() { return lights; }

	private:
		std::vector<Mesh3D> meshes;
		std::vector<std::shared_ptr<Light>> lights;
	};
}