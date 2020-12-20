#pragma once

#include "IRenderingEngine.h"
#include "TextOverlay.h"
#include "Color.h"
#include <memory>

namespace softengine
{
	class Scene3D;
	class Camera;
	class RenderPipeline3D;
	class RenderSurface;
	class RenderingWindow;
	enum class RenderingMode;

	class RenderingEngine3D : public IRenderingEngine
	{
	public:
		RenderingEngine3D(
			std::shared_ptr<Scene3D> scene,
			std::shared_ptr<Camera> camera,
			size_t pixelsWidth,
			size_t pixelsHeight
		);
		~RenderingEngine3D();

		std::unique_ptr<RenderPipeline3D>& Pipeline() { return pipeline; }
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
		std::unique_ptr<RenderPipeline3D> pipeline;
		std::unique_ptr<RenderSurface> surface;
		TextOverlay textOverlay;
		std::shared_ptr<Camera> camera;
		Color refreshColor;
		bool isInitialised;

		void RenderScene3D();
	};
}