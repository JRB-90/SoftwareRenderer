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

		if (windowEvent.key.state == SDL_PRESSED)
		{
			switch (windowEvent.key.keysym.scancode)
			{
			case SDL_Scancode::SDL_SCANCODE_W:
				currentState.up = true;
				break;
			case SDL_Scancode::SDL_SCANCODE_S:
				currentState.down = true;
				break;
			case SDL_Scancode::SDL_SCANCODE_D:
				currentState.right = true;
				break;
			case SDL_Scancode::SDL_SCANCODE_A:
				currentState.left = true;
				break;
			default:
				break;
			}
		}
		else if (windowEvent.key.state == SDL_RELEASED)
		{
			switch (windowEvent.key.keysym.scancode)
			{
			case SDL_Scancode::SDL_SCANCODE_W:
				currentState.up = false;
				break;
			case SDL_Scancode::SDL_SCANCODE_S:
				currentState.down = false;
				break;
			case SDL_Scancode::SDL_SCANCODE_D:
				currentState.right = false;
				break;
			case SDL_Scancode::SDL_SCANCODE_A:
				currentState.left = false;
				break;
			default:
				break;
			}
		}
	}
}
