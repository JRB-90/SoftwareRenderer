#pragma once
#include "SDL.h"
#include <string>

namespace softengine
{
	class RenderingWindow
	{
	public:
		RenderingWindow(
			const std::string& title,
			size_t width,
			size_t height
		);
		~RenderingWindow();

		void Show();
		void Update();
		void Close();

		SDL_Window* WindowHandle() { return window; }
		size_t Width() const { return width; }
		size_t Height() const { return height; }

	private:
		SDL_Window* window;
		const std::string title;
		size_t width;
		size_t height;
	};
}
