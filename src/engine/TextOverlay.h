#pragma once

#include <vector>
#include <string>

namespace softengine
{
	class TextOverlay
	{
	public:
		TextOverlay();

		void Update();
		//void RenderToSurface();

		std::vector<std::string>& Lines() { return lines; }

	private:
		std::vector<std::string> lines;
	};
}