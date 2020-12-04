#include "RenderingEngine2D.h"
#include "Engine.h"
#include "Frame2D.h"
#include "Utils2D.h"
#include "MathUtils.h"

#include <iostream>

using namespace softengine;

RenderingEngine2D::RenderingEngine2D(
	std::shared_ptr<Scene2D> scene, 
	size_t pixelsWidth, 
	size_t pixelsHeight)
  :
	scene(std::move(scene)),
	pixelsWidth(pixelsWidth),
	pixelsHeight(pixelsHeight),
	pixelCount(pixelsWidth * pixelsHeight),
	screenBufSize(pixelCount * 4),
	renderer(NULL),
	texture(NULL),
	pixels(NULL),
	refreshColor(
		Color(
			0.0,
			0.0,
			0.0,
			1.0
		)
	),
	isInitialised(false)
{
}

RenderingEngine2D::~RenderingEngine2D()
{
	if (!isInitialised)
	{
		delete[] pixels;
		pixels = NULL;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
	}
}

void RenderingEngine2D::InitialiseToWindow(
	RenderingWindow& window,
	RenderingMode renderingMode)
{
	renderer =
		SDL_CreateRenderer(
			window.WindowHandle(),
			-1,
			Engine::ToSDLRenderingFlag(renderingMode)
		);

	texture =
		SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			pixelsWidth,
			pixelsHeight
		);

	pixels = new Uint8[screenBufSize];
	isInitialised = true;
}

void RenderingEngine2D::WindowResized(
	size_t windowWidth, 
	size_t windowHeight)
{
	// TODO - Handle window resize
	//	      Potentially try to maintain aspect ratio with pixels?
}

void RenderingEngine2D::Render()
{
	if (!isInitialised)
	{
		return;
	}

	for (size_t j = 0; j < pixelsHeight; j++)
	{
		for (size_t i = 0; i < pixelsWidth; i++)
		{
			const size_t offset = (pixelsWidth * 4 * j) + (i * 4);
			pixels[offset + 0] = refreshColor.GetAs4B().b;
			pixels[offset + 1] = refreshColor.GetAs4B().g;
			pixels[offset + 2] = refreshColor.GetAs4B().r;
			pixels[offset + 3] = refreshColor.GetAs4B().a;
		}
	}

	RenderScene2D();

	Uint8* lockedPixels = nullptr;
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
		screenBufSize);
	SDL_UnlockTexture(texture);

	SDL_RenderCopy(
		renderer,
		texture,
		NULL,
		NULL
	);
	SDL_RenderPresent(renderer);
}

Color RenderingEngine2D::GetPixelValue(int pixel) const
{
	if (pixel < 0 ||
		pixel >= pixelCount)
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}

	const size_t offset = 4 * pixel;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

Color RenderingEngine2D::GetPixelValue(
	int pixelX,
	int pixelY) const
{
	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return Color(0.0, 0.0, 0.0, 0.0);
	}

	const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;

	return
		Color(
			pixels[offset + 2],
			pixels[offset + 1],
			pixels[offset + 0],
			pixels[offset + 3]
		);
}

void RenderingEngine2D::SetPixelValue(
	int pixel,
	Color& color)
{
	if (pixel < 0 ||
		pixel >= pixelCount)
	{
		return;
	}

	const size_t offset = 4 * pixel;
	pixels[offset + 0] = color.GetAs4B().b;
	pixels[offset + 1] = color.GetAs4B().g;
	pixels[offset + 2] = color.GetAs4B().r;
	pixels[offset + 3] = color.GetAs4B().a;
}

void RenderingEngine2D::SetPixelValue(
	int pixelX,
	int pixelY,
	Color& color)
{

	if (pixelX < 0 || pixelX >= pixelsWidth ||
		pixelY < 0 || pixelY >= pixelsHeight)
	{
		return;
	}

	const size_t offset = (pixelsWidth * pixelY * 4) + pixelX * 4;
	pixels[offset + 0] = color.GetAs4B().b;
	pixels[offset + 1] = color.GetAs4B().g;
	pixels[offset + 2] = color.GetAs4B().r;
	pixels[offset + 3] = color.GetAs4B().a;
}

void RenderingEngine2D::RenderScene2D()
{
	for (Polygon2D& polygon : scene->Polygons())
	{
		RenderPolygon(polygon);
	}

	for (Line2D& line : scene->Lines())
	{
		RenderLine(line);
	}

	for (Point2D& point : scene->Points())
	{
		RenderPoint(point);
	}
}

void RenderingEngine2D::RenderPoint(Point2D& point)
{
	Vector2D p = MathUtils::TransformPointFor2D(
		point.Position(),
		point.Transform()
	);
	SetPixelValue(
		(size_t)p.X(),
		(size_t)p.Y(),
		point.GetColor()
	);
}

void RenderingEngine2D::RenderLine(Line2D& line)
{
	Vector2D p1 = MathUtils::TransformPointFor2D(
		line.P1(),
		line.Transform()
	);

	Vector2D p2 = MathUtils::TransformPointFor2D(
		line.P2(),
		line.Transform()
	);

	int yMax, yMin;
	RenderLinePoints(
		p1,
		p2,
		line.GetColor(),
		yMax,
		yMin
	);
}

void RenderingEngine2D::RenderLinePoints(
	Vector2D p1,
	Vector2D p2,
	Color color,
	int& yMax,
	int& yMin)
{
	double x = p1.X();
	double y = p1.Y();
	yMax = yMin = y;
	double dx = p2.X() - p1.X();
	double dy = p2.Y() - p1.Y();
	int steps;

	if (std::abs(dx) > std::abs(dy))
	{
		steps = (int)std::abs(dx);
	}
	else
	{
		steps = (int)std::abs(dy);
	}

	double xInc = dx / (double)steps;
	double yInc = dy / (double)steps;

	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yInc;
		SetPixelValue(
			x,
			y,
			color
		);

		if (y > yMax)
		{
			yMax = y;
		}
		if (y < yMin)
		{
			yMin = y;
		}
	}
}

void RenderingEngine2D::RenderTriangle(Triangle2D& triangle)
{
	Vector2D p0 = triangle.P1();
	Vector2D p1 = triangle.P2();
	Vector2D p2 = triangle.P3();
	
	if (p1.Y() < p0.Y())
	{
		Vector2D temp = p1;
		p1 = p0;
		p0 = temp;
	}
	if (p2.Y() < p0.Y())
	{
		Vector2D temp = p2;
		p2 = p0;
		p0 = temp;
	}
	if (p2.Y() < p1.Y())
	{
		Vector2D temp = p2;
		p2 = p1;
		p1 = temp;
	}

	std::vector<int> x01 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(), 
			p1.X(),
			p1.Y() 
		);

	std::vector<int> x12 =
		Utils2D::InterpolateXPixelValues(
			p1.X(),
			p1.Y(),
			p2.X(),
			p2.Y()
		);

	std::vector<int> x02 =
		Utils2D::InterpolateXPixelValues(
			p0.X(),
			p0.Y(),
			p2.X(),
			p2.Y()
		);

	x01.pop_back();
	std::vector<int> x012;
	for (auto x : x01)
	{
		x012.push_back(x);
	}
	for (auto x : x12)
	{
		x012.push_back(x);
	}

	std::vector<int> xLeft;
	std::vector<int> xRight;
	int m = x02.size() / 2;
	if (x02[m] < x012[m])
	{
		xLeft = x02;
		xRight = x012;
	}
	else
	{
		xLeft = x012;
		xRight = x02;
	}

	for (int y = p0.Y(); y < p2.Y(); y++)
	{
		for (int x = xLeft[y - p0.Y()]; x < xRight[y - p0.Y()]; x++)
		{
			SetPixelValue(
				x,
				y,
				triangle.GetColor()
			);
		}
	}
}

void RenderingEngine2D::RenderPolygon(Polygon2D& polygon)
{
	if (polygon.Points().size() == 0)
	{
		return;
	}
	else if (polygon.Points().size() == 1)
	{
		Vector2D p = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[0]),
			polygon.Transform()
		);
		RenderPoint(
			Point2D(
				p,
				polygon.GetColor()
			)
		);
	}
	else if (polygon.Points().size() == 2)
	{
		Vector2D p1 = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[0]),
			polygon.Transform()
		);
		Vector2D p2 = MathUtils::TransformPointFor2D(
			Vector2D(polygon.Points()[1]),
			polygon.Transform()
		);

		RenderLine(
			Line2D(
				p1,
				p2,
				polygon.GetColor()
			)
		);
	}
	else
	{
		RenderPolygonFilled(polygon);
		//RenderPolygonLines(polygon);
	}
}

void RenderingEngine2D::RenderPolygonLines(Polygon2D& polygon)
{
	std::vector<Vector2D> transformedPoints;
	for (size_t i = 0; i < polygon.Points().size(); i++)
	{
		transformedPoints.push_back(
			MathUtils::TransformPointFor2D(
				Vector2D(polygon.Points()[i]),
				polygon.Transform()
			)
		);
	}

	for (size_t i = 0; i < polygon.Points().size() - 1; i++)
	{
		RenderLine(
			Line2D(
				transformedPoints[i],
				transformedPoints[i + 1],
				Color::White
			)
		);
	}
	RenderLine(
		Line2D(
			transformedPoints[transformedPoints.size() - 1],
			transformedPoints[0],
			Color::White
		)
	);
}

void RenderingEngine2D::RenderPolygonFilled(Polygon2D& polygon)
{
	if (!polygon.IsValid())
	{
		std::cerr << "Attempted to render invlaid polygon" << std::endl;

		return;
	}

	std::vector<Vector2D> transformedPoints;
	for (size_t i = 0; i < polygon.Points().size(); i++)
	{
		transformedPoints.push_back(
			MathUtils::TransformPointFor2D(
				Vector2D(polygon.Points()[i]),
				polygon.Transform()
			)
		);
	}

	for (size_t i = 1; i < polygon.Points().size() - 1; i++)
	{
		RenderTriangle(
			Triangle2D(
				transformedPoints[0],
				transformedPoints[i],
				transformedPoints[i + 1],
				polygon.GetColor()
			)
		);
	}
}
