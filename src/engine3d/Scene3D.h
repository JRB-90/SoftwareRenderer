#pragma once

#include "IScene.h"

namespace softengine
{
	class Scene3D : public IScene
	{
	public:
		Scene3D();

		void ClearAll() override;

	private:
	};
}