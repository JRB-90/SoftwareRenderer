#pragma once

#include "IScene.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include <memory>

namespace softengine
{
	class IRenderingEngine
	{
	public:
		virtual void Render() = 0;
		virtual void InitialiseToWindow(
			RenderingWindow& window,
			RenderingMode renderingMode
		) = 0;
		virtual void WindowResized(
			size_t windowWidth,
			size_t windowHeight
		) = 0;
	};
}