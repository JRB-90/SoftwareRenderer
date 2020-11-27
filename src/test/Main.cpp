#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "SDL.h"
#undef main

const size_t WINDOW_WIDTH = 640;
const size_t WINDOW_HEIGHT = 480;
const size_t SCREEN_WIDTH = 640;
const size_t SCREEN_HEIGHT = 480;
const size_t PIXEL_COUNT = SCREEN_WIDTH * SCREEN_HEIGHT;
const size_t SCREEN_BUF_SIZE = PIXEL_COUNT * 4;
Uint8 pixels[SCREEN_BUF_SIZE] = { 0 };

int main(int argc, const char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window =
		SDL_CreateWindow(
			"Test",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
		);

	SDL_Renderer* renderer =
		SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_SOFTWARE
		);

	SDL_RendererInfo info;
	SDL_GetRendererInfo(
		renderer,
		&info
	);

	std::cout << "Renderer name: " << info.name << std::endl;
	std::cout << "Texture formats: " << std::endl;
	for (size_t i = 0; i < info.num_texture_formats; i++)
	{
		std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << std::endl;
	}

	SDL_Texture* texture =
		SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
		);

	std::srand(std::time(nullptr));
	bool isRunning = true;
	SDL_Event windowEvent;
	Uint32 previousTicks = SDL_GetTicks();

	while (isRunning)
	{
		SDL_PollEvent(&windowEvent);

		switch (windowEvent.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}

		SDL_SetRenderDrawColor(
			renderer,
			0,
			0,
			0,
			255
		);
		SDL_RenderClear(renderer);

		for (size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			for (size_t i = 0; i < SCREEN_WIDTH; i++)
			{
				const size_t offset = (SCREEN_WIDTH * 4 * j) + (i * 4);
				pixels[offset + 0] = (Uint8)std::rand();
				pixels[offset + 1] = (Uint8)std::rand();
				pixels[offset + 2] = (Uint8)std::rand();
				pixels[offset + 3] = 255;
			}
		}

		unsigned char* lockedPixels = nullptr;
		int pitch = 0;
		SDL_LockTexture(
			texture,
			NULL,
			reinterpret_cast<void**>(&lockedPixels),
			&pitch
		);
		std::memcpy(
			lockedPixels,
			pixels,
			SCREEN_BUF_SIZE);
		SDL_UnlockTexture(texture);

		SDL_RenderCopy(
			renderer,
			texture,
			NULL,
			NULL
		);
		SDL_RenderPresent(renderer);

		Uint32 currentTicks = SDL_GetTicks();
		Uint32 deltaTicks = currentTicks - previousTicks;
		std::cout << "Ticks passed: " << deltaTicks << std::endl;
		std::cout << "Seconds passed: " << (double)deltaTicks / 1000.0 << std::endl;
		std::cout << "FPS: " << 1.0 / ((double)deltaTicks / 1000.0) << std::endl << std::endl;
		previousTicks = currentTicks;
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}