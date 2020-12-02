#include "Engine.h"
#include "IRenderingEngine.h"
#include "RenderingEngine2D.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "IScene.h"
#include "Scene2D.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Polygon2D.h"
#include "Frame2D.h"

#include <iostream>
#include <memory>
#include <random>
#include <ctime>
#include <cmath>

using namespace softengine;

const size_t WINDOW_WIDTH = 640;
const size_t WINDOW_HEIGHT = 480;
const size_t PIXELS_WIDTH = 640;
const size_t PIXELS_HEIGHT = 480;
const int UPDATE_RATE = 20;

std::shared_ptr<Scene2D> scene;

void SetupScene();
void Update(double delta);

int main(int argc, const char* argv[])
{
	std::cout << "Starting..." << std::endl;

	std::srand(std::time(nullptr));
	scene = std::make_shared<Scene2D>();
	SetupScene();

	std::shared_ptr<IRenderingEngine> renderingEngine =
		std::make_shared<RenderingEngine2D>(
			scene,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
		);

	Engine engine(
		renderingEngine,
		RenderingMode::Software,
		"Engine Test",
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		UPDATE_RATE,
		true
	);

	engine.RegisterUpdateCallback(Update);
	engine.Run();

	std::cout << "Finished" << std::endl;

	return 0;
}

void SetupScene()
{
	//for (size_t i = 0; i < 100; i++)
	//{
	//	scene->Points().push_back(
	//		Point2D(
	//			Vector2D(
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_WIDTH,
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_HEIGHT
	//			),
	//			Color(
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				1.0
	//			)
	//		)
	//	);
	//}

	//for (size_t j = 0; j < 20; j++)
	//{
	//	scene->Lines().push_back(
	//		Line2D(
	//			Vector2D(
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_WIDTH,
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_HEIGHT
	//			),
	//			Vector2D(
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_WIDTH,
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_HEIGHT
	//			),
	//			Color(
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				1.0
	//			)
	//		)
	//	);
	//}

	std::vector<Vector2D> polyPoints;
	polyPoints.push_back(Vector2D(-50, 50));
	polyPoints.push_back(Vector2D(-50, -50));
	polyPoints.push_back(Vector2D(40, -50));
	Polygon2D triangle(
		polyPoints,
		Color::Cyan
	);
	triangle.Transform(
		Frame2D(
			Vector2D(300, 450)
		)
	);
	scene->Polygons().push_back(triangle);

	std::vector<Vector2D> polyPoints2;
	polyPoints2.push_back(Vector2D(-50, -50));
	polyPoints2.push_back(Vector2D(-50, 50));
	polyPoints2.push_back(Vector2D(50, 50));
	polyPoints2.push_back(Vector2D(50, -50));
	Polygon2D square(
		polyPoints2,
		Color::Magenta
	);
	scene->Polygons().push_back(square);

	std::vector<Vector2D> polyPoints3;
	polyPoints3.push_back(Vector2D(0, -40));
	polyPoints3.push_back(Vector2D(-48, -5));
	polyPoints3.push_back(Vector2D(-29, 50));
	polyPoints3.push_back(Vector2D(29, 50));
	polyPoints3.push_back(Vector2D(48, -5));
	Polygon2D pentagon(
		polyPoints3,
		Color::Yellow
	);
	pentagon.Transform(
		Frame2D(
			Vector2D(
				200,
				200
			),
			0
		)
	);
	scene->Polygons().push_back(pentagon);

	//for (size_t i = 0; i < 1; i++)
	//{
	//	//size_t randSize = 6;
	//	size_t randSize = (size_t)((((double)std::rand() / RAND_MAX) * 8.0) + 2);
	//	std::vector<Vector2D> pPoints;
	//	for (size_t k = 0; k < randSize; k++)
	//	{
	//		pPoints.push_back(
	//			Vector2D(
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_WIDTH,
	//				((double)std::rand() / RAND_MAX) * (double)PIXELS_HEIGHT
	//			)
	//		);
	//	}
	//	scene->Polygons().push_back(
	//		Polygon2D(
	//			pPoints,
	//			Color(
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				(double)std::rand() / RAND_MAX,
	//				1.0
	//			)
	//		)
	//	);
	//}
}

double a = 0.0;

void Update(double delta)
{
	// Update scene here

	scene->Polygons()[0].Transform().Position(
		Vector2D(
			300 + (std::sin(SDL_GetPerformanceCounter() / 20000) * 30),
			400 + (std::cos(SDL_GetPerformanceCounter() / 20000) * 30)
		)
	);
	scene->Polygons()[0].Transform().Angle(-a * 2);

	scene->Polygons()[1].Transform().Position(
		Vector2D(
			400 + (std::sin(SDL_GetPerformanceCounter() / 10000) * 20),
			200 + (std::cos(SDL_GetPerformanceCounter() / 10000) * 20)
		)
	);

	scene->Polygons()[2].Transform().Angle(a);
	a += 1.0;
}
