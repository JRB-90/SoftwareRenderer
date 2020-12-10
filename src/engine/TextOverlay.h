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

		void RenderToSurface(RenderSurface& surface);

		std::vector<std::string>& Lines() { return lines; }

	private:
		ResourceLoader resourceLoader;
		std::vector<std::string> lines;
		int fontSize;
		Color4B fontColor;
	};
}