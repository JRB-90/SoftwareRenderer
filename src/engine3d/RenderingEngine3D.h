#pragma once

#include "IRenderingEngine.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Color.h"
#include "Scene3D.h"
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

		Color RefreshColor() const { return refreshColor; }
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
		const size_t pixelsWidth;
		const size_t pixelsHeight;
		const size_t pixelCount;
		const size_t screenBufSize;
		std::shared_ptr<Scene3D> scene;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint8* pixels;
		Color refreshColor;
		bool isInitialised;

		Color GetPixelValue(size_t pixel) const;
		Color GetPixelValue(
			size_t pixelX,
			size_t pixelY) const;
		void SetPixelValue(
			size_t pixel,
			Color& color
		);
		void SetPixelValue(
			size_t pixelX,
			size_t pixelY,
			Color& color
		);

		void RenderScene3D();
		//void RenderPoint(Point3D& point);
	};
}