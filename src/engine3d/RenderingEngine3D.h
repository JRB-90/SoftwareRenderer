#pragma once

#include "IRenderingEngine.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Scene3D.h"
#include "Color.h"
#include "RenderSurface.h"
#include "TextOverlay.h"
#include "SDL.h"
#include <memory>

namespace softengine
{
	class RenderingEngine3D : public IRenderingEngine
	{
	public:
		RenderingEngine3D(
			std::shared_ptr<Scene3D> scene,
			size_t pixelsWidth,
			size_t pixelsHeight
		);
		~RenderingEngine3D();

		TextOverlay& GetTextOverLay() { return textOverlay; }
		Color& RefreshColor() { return refreshColor; }
		void RefreshColor(Color& refreshColor) { this->refreshColor = refreshColor; }

		void InitialiseToWindow(
			RenderingWindow& window,
			RenderingMode renderingMode
		);
		void WindowResized(
			size_t windowWidth,
			size_t windowHeight
		);
		void Render() override;

	private:
		size_t pixelsWidth;
		size_t pixelsHeight;
		size_t pixelCount;
		size_t screenBufSize;
		std::shared_ptr<Scene3D> scene;
		std::unique_ptr<RenderSurface> surface;
		TextOverlay textOverlay;
		Color refreshColor;
		bool isInitialised;

		void RenderScene3D();
	};
}