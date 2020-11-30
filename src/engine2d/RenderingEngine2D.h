#pragma once

#include "IRenderingEngine.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "Scene2D.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Triangle2D.h"
#include "Polygon2D.h"
#include "SDL.h"
#include <memory>

namespace softengine
{
	class RenderingEngine2D : public IRenderingEngine
	{
	public:
		RenderingEngine2D(
			std::shared_ptr<Scene2D> scene,
			size_t pixelsWidth,
			size_t pixelsHeight
		);
		~RenderingEngine2D();

		Color RefreshColor() const { return refreshColor; }
		void RefreshColor(Color& refreshColor) { this->refreshColor = refreshColor; }

		void InitialiseToWindow(
			RenderingWindow& window,
			RenderingMode renderingMode
		);
		void WindowResized(
			size_t windowWidth,
			size_t windowHeight
		);
		void Render() override;

	private:
		const size_t pixelsWidth;
		const size_t pixelsHeight;
		const size_t pixelCount;
		const size_t screenBufSize;;
		std::shared_ptr<Scene2D> scene;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint8* pixels;
		Color refreshColor;
		bool isInitialised;

		Color GetPixelValue(size_t pixel) const;
		Color GetPixelValue(
			size_t pixelX,
			size_t pixelY) const;
		void SetPixelValue(
			size_t pixel,
			Color& color
		);
		void SetPixelValue(
			size_t pixelX,
			size_t pixelY,
			Color& color
		);

		void RenderScene2D();
		void RenderPoint(Point2D& point);
		void RenderLine(Line2D& line);
		void RenderLinePoints(
			Vector2D p1,
			Vector2D p2,
			Color color,
			int& yMax,
			int& yMin
		);
		void RenderTriangle(Triangle2D& triangle);
		void RenderPolygon(Polygon2D& polygon);
		void RenderPolygonLines(Polygon2D& polygon);
		void RenderPolygonFilled(Polygon2D& polygon);
	};
}