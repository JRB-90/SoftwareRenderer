#pragma once

#include "RenderingWindow.h"
#include "IRenderingEngine.h"
#include "ResourceManager.h"
#include "RenderingMode.h"
#include "InputHandler.h"
#include "InputState.h"
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
		void RegisterUpdateCallback(void (*updateCallback)(InputState, double));

		ResourceManager& GetResourceManager() { return resourceManager; }

		static SDL_RendererFlags ToSDLRenderingFlag(RenderingMode renderingMode);

	private:
		RenderingWindow renderingWindow;
		std::shared_ptr<IRenderingEngine> renderingEngine;
		ResourceManager resourceManager;
		InputHandler inputHandler;
		RenderingMode renderingMode;
		int updateFrequency;
		bool debugModeEnabled;
		bool isRunning;
		std::thread runThread;
		void (*updateCallback)(InputState, double);

		InputState PollInput();
		void Update(
			InputState inputstate,
			double delta
		);
		void Render();
	};
}