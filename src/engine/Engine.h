#pragma once

#include "RenderingWindow.h"
#include "IRenderingEngine.h"
#include "RenderingMode.h"
#include "SDL.h"
#undef main
#include <thread>
#include <memory>
#include <string>

namespace softengine
{
	class Engine
	{
	public:
		Engine(
			std::shared_ptr<IRenderingEngine> renderingEngine,
			RenderingMode renderingMode,
			const std::string& windowTitle,
			size_t windowWidth,
			size_t windowHeight,
			int updateFrequency,
			bool debugModeEnabled = false);
		~Engine();

		void Run();
		void RegisterUpdateCallback(void (*updateCallback)(double));

		static SDL_RendererFlags ToSDLRenderingFlag(RenderingMode renderingMode);

	private:
		RenderingWindow renderingWindow;
		std::shared_ptr<IRenderingEngine> renderingEngine;
		RenderingMode renderingMode;
		int updateFrequency;
		bool debugModeEnabled;
		bool isRunning;
		std::thread runThread;
		void (*updateCallback)(double);

		void PollInput();
		void Update(double delta);
		void Render();
	};
}