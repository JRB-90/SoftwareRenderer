#pragma once
#include "SDL.h"
#include <memory>

namespace softengine
{
	class Input
	{
	public:
		Input();

		void Update();

		bool IsQuitRequested() { return isQuitRequested; }

	private:
		std::unique_ptr<SDL_Event> windowEvent;
		bool isQuitRequested;
	};
}