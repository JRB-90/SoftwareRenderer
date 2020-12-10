#include "TextOverlay.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace softengine;

TextOverlay::TextOverlay(
	int fontSize,
	Color fontColor)
	:
	fontSize(fontSize),
	fontColor(fontColor.GetAs4B())
{
}

void TextOverlay::RenderToSurface(RenderSurface& surface)
{
	if (lines.size() == 0)
	{
		return;
	}

	TTF_Font* font = resourceLoader.LoadFontResource(
		"FreeMono.ttf",
		fontSize
	);
	SDL_Color color =
	{
		fontColor.r,
		fontColor.g,
		fontColor.b
	};

	for (size_t i = 0; i < lines.size(); i++)
	{
		SDL_Surface* textSurface =
			TTF_RenderText_Solid(
				font,
				lines[i].c_str(),
				color
			);

		SDL_Texture* texture = surface.CreateSDLTexture(textSurface);
		SDL_Rect textRect;
		textRect.x = 0;
		textRect.y = textSurface->h * i;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		surface.RenderTexture(
			textRect,
			texture
		);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(texture);
	}
}
