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
#include "ResourceLoader.h"
#include "Sprite2D.h"
#include "InputState.h"

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
void Update(
	InputState inputState,
	double delta
);

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
		Color(
			0.2,
			0.1,
			0.1,
			1.0
		)
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
	try
	{
		ResourceLoader imageLoader;
		Texture texture = imageLoader.LoadImageResource("sprites\\cat.png");
		Sprite2D cat(texture);
		cat.Transform().Position(
			Vector2D(200, 200)
		);
		scene->Sprites().push_back(cat);
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Update(
	InputState inputState, 
	double delta)
{
	double speed = 10.0 * delta;

	if (inputState.up)
	{
		scene->Sprites()[0].Transform().Position().Y(
			scene->Sprites()[0].Transform().Position().Y() - speed
		);
	}
	if (inputState.down)
	{
		scene->Sprites()[0].Transform().Position().Y(
			scene->Sprites()[0].Transform().Position().Y() + speed
		);
	}
	if (inputState.left)
	{
		scene->Sprites()[0].Transform().Position().X(
			scene->Sprites()[0].Transform().Position().X() - speed
		);
	}
	if (inputState.right)
	{
		scene->Sprites()[0].Transform().Position().X(
			scene->Sprites()[0].Transform().Position().X() + speed
		);
	}
}
