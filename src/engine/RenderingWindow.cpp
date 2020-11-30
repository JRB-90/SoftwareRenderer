#include "RenderingWindow.h"

using namespace softengine;

RenderingWindow::RenderingWindow(
	const std::string& title,
	size_t width,
	size_t height)
  :
	title(title),
	width(width),
	height(height),
	window(NULL)
{
}

RenderingWindow::~RenderingWindow()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
}

void RenderingWindow::Show()
{
	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_RESIZABLE
	);
}

void RenderingWindow::Close()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
}
