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

		currentState.windowResizeRequested = false;

		switch (windowEvent.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			currentState.windowResizeRequested = true;
			currentState.windowSizeWidth = windowEvent.window.data1;
			currentState.windowSizeHeight = windowEvent.window.data2;
			break;
		default:
			currentState.windowResizeRequested = false;
			currentState.windowSizeWidth = 0;
			currentState.windowSizeHeight = 0;
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
			default:
				break;
			}
		}
	}
}
