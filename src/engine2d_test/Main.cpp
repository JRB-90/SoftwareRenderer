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
#include "ImageLoader.h"
#include "Sprite2D.h"

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

std::unique_ptr<Engine> engine;
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

	renderingEngine->RefreshColor(
		Color(Color::White)
	);

	engine = std::make_unique<Engine>(
		renderingEngine,
		RenderingMode::Software,
		"Engine 2D Test",
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		UPDATE_RATE,
		true
	);

	engine->RegisterUpdateCallback(Update);
	engine->Run();

	std::cout << "Finished" << std::endl;

	return 0;
}

void SetupScene()
{
	Texture texture;
	if (engine->GetResourceManager().LoadImageResource(
		"cat.png",
		texture
	))
	{
		Sprite2D cat(texture);
		cat.Transform().Position(
			Vector2D(200, 200)
		);
		scene->Sprites().push_back(cat);
	}
}

void Update(double delta)
{
	
}
