#pragma once

#include "InputState.h"

namespace softengine
{
	class InputHandler
	{
	public:
		InputHandler();
		
		void Update();
		
		InputState& GetCurrentState() { return currentState; };

	private:
		InputState currentState;
	};
}