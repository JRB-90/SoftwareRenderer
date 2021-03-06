#pragma once

#include "IRenderingEngine.h"
#include "TextOverlay.h"
#include "PipelineConfiguration3D.h"
#include "Color.h"
#include "RenderPipeline3D.h"
#include <memory>

namespace softengine
{
	class Scene3D;
	class Camera;
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
		RenderingEngine3D(
			std::shared_ptr<Scene3D> scene,
			std::shared_ptr<Camera> camera,
			size_t pixelsWidth,
			size_t pixelsHeight,
			PipelineConfiguration pipelineConfiguration
		);
		~RenderingEngine3D();

		PipelineConfiguration& GetPipelineConfiguration() { return pipeline->Configuration(); }
		TextOverlay& GetTextOverLay() { return textOverlay; }
		Color& RefreshColor() { return refreshColor; }
		void RefreshColor(Color& refreshColor) { this->refreshColor = refreshColor; }

		void InitialiseToWindow(
			RenderingWindow& window,
			RenderingMode renderingMode
		);
		void WindowResized(RenderingWindow& window);
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
	};
}