#pragma once

#include "RenderSurface.h"
#include <vector>
#include <string>

namespace softengine
{
	class TextOverlay
	{
	public:
		TextOverlay();

		void Update();
		void RenderToSurface(RenderSurface& surface);

		std::vector<std::string>& Lines() { return lines; }

	private:
		std::vector<std::string> lines;
	};
}