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
		bool rotL = false;
		bool rotR = false;

		bool noShading = false;
		bool normalShading = false;
		bool flatShading = false;
		bool phongShading = false;

		bool wireFrameModeOff = false;
		bool wireFrameModeOn = false;

		bool noCulling = false;
		bool cwCulling = false;
		bool acwCulling = false;

		bool noDepthCheck = false;
		bool lessThanDepthCheck = false;
		bool moreThanDepthCheck = false;

		bool noTexture = false;
		bool texture = false;
	};
}