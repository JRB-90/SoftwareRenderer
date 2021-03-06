#include "Engine.h"

#include "Profiler.h"
#include <iostream>
#include <chrono>
#include <sstream>

using namespace softengine;

Engine::Engine(
	std::shared_ptr<IRenderingEngine> renderingEngine,
	RenderingMode renderingMode,
	const std::string& windowTitle,
	size_t windowWidth,
	size_t windowHeight,
	int updateFrequency,
	bool debugModeEnabled)
  :
	renderingEngine(std::move(renderingEngine)),
	renderingMode(renderingMode),
	updateFrequency(updateFrequency),
	debugModeEnabled(debugModeEnabled),
	isRunning(false),
	renderingWindow(
		windowTitle,
		windowWidth,
		windowHeight
	),
	updateCallback(NULL)
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Engine::~Engine()
{
	SDL_Quit();
}

void Engine::Run()
{
	renderingWindow.Show();
	renderingEngine->InitialiseToWindow(
		renderingWindow,
		renderingMode
	);
	isRunning = true;

	double targetTime = 1.0 / (double)updateFrequency;
	Uint64 targetInterval = SDL_GetPerformanceFrequency() / updateFrequency;
	Uint64 current = SDL_GetPerformanceCounter();
	Uint64 previous = current;
	Profiler profiler;

	while (isRunning)
	{
		current = SDL_GetPerformanceCounter();
		Uint64 delta = current - previous;
		if (delta > targetInterval)
		{
			double timeTaken = (double)delta / (double)SDL_GetPerformanceFrequency();
			previous = current;

			std::printf("======================================================================================\n");
			profiler.ResetProfileRun();
			InputState inputState = PollInput();
			profiler.AddTiming("Input Handling");
			Update(inputState, timeTaken / targetTime);
			profiler.AddTiming("Update Total");
			Render();
			profiler.AddTiming("Render Total");

			if (debugModeEnabled)
			{
				std::stringstream ss;
				ss << "Time taken: " << timeTaken << "s" << std::endl;
				ss << "FPS: " << 1.0 / timeTaken << std::endl;
				ss << "Delta percentage: " << timeTaken / targetTime;
				//std::cout << "\033[2J" << "" << "\033[H";
				//std::cout << ss.str();
				renderingEngine->GetTextOverLay().SetText(ss.str());
				profiler.PrintTimings();
				std::printf("\n");
			}
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(0));
	}

	renderingWindow.Close();
}

void Engine::RegisterUpdateCallback(void(*updateCallback)(InputState, double))
{
	this->updateCallback = updateCallback;
}

SDL_RendererFlags Engine::ToSDLRenderingFlag(RenderingMode renderingMode)
{
	switch (renderingMode)
	{
	case RenderingMode::Software:
		return SDL_RendererFlags::SDL_RENDERER_SOFTWARE;
	case RenderingMode::Hardware:
		return SDL_RendererFlags::SDL_RENDERER_ACCELERATED;
	default:
		return SDL_RendererFlags::SDL_RENDERER_SOFTWARE;
	}
}

InputState Engine::PollInput()
{
	inputHandler.Update();
	InputState inputState = inputHandler.GetCurrentState();

	if (inputState.isQuitRequested)
	{
		isRunning = false;

		return inputState;
	}
	
	if (inputState.windowResizeRequested)
	{
		renderingWindow.Update();
		renderingEngine->WindowResized(renderingWindow);
	}

	return inputState;
}

void Engine::Update(
	InputState inputState, 
	double delta)
{
	if (updateCallback != NULL)
	{
		updateCallback(inputState, delta);
	}
}

void Engine::Render()
{
	renderingEngine->Render();
}
