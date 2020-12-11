#pragma once

#include "ResourceLoader.h"
#include "RenderSurface.h"
#include "Color.h"
#include <vector>
#include <string>

namespace softengine
{
	class TextOverlay
	{
	public:
		TextOverlay(
			int fontSize,
			Color fontColor
		);

		void SetText(const std::string& text);
		void RenderToSurface(RenderSurface& surface);

	private:
		ResourceLoader resourceLoader;
		std::vector<std::string> lines;
		int fontSize;
		Color4B fontColor;
	};
}