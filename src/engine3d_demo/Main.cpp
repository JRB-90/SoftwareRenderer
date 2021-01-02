#include "Engine.h"
#include "RenderingEngine3D.h"
#include "Scene3D.h"
#include "Camera.h"

#include <iostream>
#include <random>
#include <ctime>

using namespace softengine;

const size_t WINDOW_WIDTH = 640;
const size_t WINDOW_HEIGHT = 480;
const size_t PIXELS_WIDTH = 640;
const size_t PIXELS_HEIGHT = 480;
const int UPDATE_RATE = 30;

std::shared_ptr<Scene3D> scene;
std::shared_ptr<Camera> camera;
std::shared_ptr<RenderingEngine3D> renderingEngine;

void SetupScene();
void Update(
	InputState inputState,
	double delta
);

int main(int argc, const char* argv[])
{
	std::cout << "Starting..." << std::endl;

	std::srand(std::time(nullptr));
	scene = std::make_shared<Scene3D>();
	SetupScene();

	camera =
		std::make_shared<Camera>(
			PIXELS_WIDTH,
			PIXELS_HEIGHT,
			60.0,
			0.1,
			10000.0
			);
	camera->Position(Frame3D(Vector3D(0.0, 3.0, 5.0)));

	renderingEngine =
		std::make_shared<RenderingEngine3D>(
			scene,
			camera,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
			);
	renderingEngine->RefreshColor(Color(0.1, 0.1, 0.1, 1.0));

	Engine engine(
		renderingEngine,
		RenderingMode::Software,
		"Engine 3D Test",
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
}

void Update(
	InputState inputState,
	double delta)
{
}
