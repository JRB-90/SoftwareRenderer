#include "Input.h"

using namespace softengine;

Input::Input()
  :
	isQuitRequested(false)
{
}

void Input::Update()
{
	SDL_PollEvent(windowEvent.get());

	switch (windowEvent->type)
	{
	case SDL_QUIT:
		isQuitRequested = true;
		break;
	default:
		break;
	}
}
