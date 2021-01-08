#include "InputHandler.h"
#include "SDL.h"

using namespace softengine;

InputHandler::InputHandler()
{
}

void InputHandler::Update()
{
	SDL_Event windowEvent;

	while (SDL_PollEvent(&windowEvent))
	{
		switch (windowEvent.type)
		{
		case SDL_QUIT:
			currentState.isQuitRequested = true;
			return;
		default:
			break;
		}

		switch (windowEvent.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			currentState.windowSizeWidth = windowEvent.window.data1;
			currentState.windowSizeHeight = windowEvent.window.data2;
			currentState.windowResizeRequested = true;

			return;
		default:
			currentState.windowSizeWidth = 0;
			currentState.windowSizeHeight = 0;
			currentState.windowResizeRequested = false;
			break;
		}

		if (windowEvent.key.state == SDL_PRESSED ||
			windowEvent.key.state == SDL_RELEASED)
		{
			bool state = windowEvent.key.state == SDL_PRESSED;
			switch (windowEvent.key.keysym.scancode)
			{
			case SDL_Scancode::SDL_SCANCODE_W:
				currentState.up = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_S:
				currentState.down = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_D:
				currentState.right = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_A:
				currentState.left = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_Z:
				currentState.in = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_X:
				currentState.out = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_Q:
				currentState.rotL = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_E:
				currentState.rotR = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_T:
				currentState.stopSpin = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_Y:
				currentState.startSpin = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_U:
				currentState.noShading = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_I:
				currentState.normalShading = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_O:
				currentState.flatShading = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_P:
				currentState.phongShading = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_K:
				currentState.wireFrameModeOff = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_L:
				currentState.wireFrameModeOn = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_G:
				currentState.noCulling = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_H:
				currentState.acwCulling = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_J:
				currentState.cwCulling = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_B:
				currentState.noDepthCheck = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_N:
				currentState.moreThanDepthCheck = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_M:
				currentState.lessThanDepthCheck = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_C:
				currentState.noTexture = state;
				break;
			case SDL_Scancode::SDL_SCANCODE_V:
				currentState.texture = state;
				break;
			default:
				break;
			}
		}
	}
}
