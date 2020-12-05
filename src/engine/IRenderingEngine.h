#pragma once

#include "IScene.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Color.h"
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

		virtual Color RefreshColor() const = 0;
		virtual void RefreshColor(Color& refreshColor) = 0;
	};
}