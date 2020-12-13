#pragma once

namespace softengine
{
	struct InputState
	{
		bool isQuitRequested = false;
		bool windowResizeRequested = false;
		size_t windowSizeWidth = 0;
		size_t windowSizeHeight = 0;

		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;
		bool in = false;
		bool out = false;
	};
}