#include "Engine.h"
#include "RenderingEngine3D.h"
#include "Scene3D.h"

#include "Vector3D.h"
#include "Frame3D.h"
#include "Rotation3D.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"

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

void SetupScene();
void Update(
	InputState inputstate,
	double delta
);

int main(int argc, const char* argv[])
{
	std::cout << "Starting..." << std::endl;

	std::srand(std::time(nullptr));
	scene = std::make_shared<Scene3D>();
	SetupScene();

	std::shared_ptr<IRenderingEngine> renderingEngine =
		std::make_shared<RenderingEngine3D>(
			scene,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
		);

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
	InputState inputstate,
	double delta)
{

}
