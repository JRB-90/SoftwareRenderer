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

#include <iostream>
#include <memory>
#include <random>
#include <ctime>

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

	scene->Lines().push_back(
		Line2D(
			Vector2D(),
			Vector2D()
		)
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
	polyPoints.push_back(Vector2D(100, 100));
	polyPoints.push_back(Vector2D(120, 200));
	polyPoints.push_back(Vector2D(200, 250));
	scene->Polygons().push_back(
		Polygon2D(
			polyPoints,
			Color::Cyan
		)
	);

	std::vector<Vector2D> polyPoints2;
	polyPoints2.push_back(Vector2D(300, 300));
	polyPoints2.push_back(Vector2D(300, 400));
	polyPoints2.push_back(Vector2D(400, 400));
	polyPoints2.push_back(Vector2D(400, 300));
	scene->Polygons().push_back(
		Polygon2D(
			polyPoints2,
			Color::Magenta
		)
	);

	std::vector<Vector2D> polyPoints3;
	polyPoints3.push_back(Vector2D(450, 50));
	polyPoints3.push_back(Vector2D(402, 85));
	polyPoints3.push_back(Vector2D(421, 140));
	polyPoints3.push_back(Vector2D(479, 140));
	polyPoints3.push_back(Vector2D(498, 85));
	scene->Polygons().push_back(
		Polygon2D(
			polyPoints3,
			Color::Yellow
		)
	);

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

void Update(double delta)
{
	// Update scene here
}
