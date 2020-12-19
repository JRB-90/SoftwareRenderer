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
#include "Vertex2D.h"

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
const int UPDATE_RATE = 30;

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
			0.0,
			0.0,
			0.0,
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
		cat.Transform().Translation(
			Vector2D(200, 200)
		);
		scene->Sprites().push_back(cat);
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::vector<size_t> indices = { 0, 1, 2};
	std::vector<Vertex2D> vertices = 
	{
		Vertex2D(Vector2D(30.0, 0.0), Color::Red),
		Vertex2D(Vector2D(0.0, 100.0), Color::Green),
		Vertex2D(Vector2D(50.0, 50.0), Color::Blue)
	};
	Polygon2D triPoly(indices, vertices, DrawType::Triangles);
	triPoly.Transform(Frame2D(Vector2D(300, 200)));
	triPoly.Transform().Scale(2.0);
	scene->Polygons().push_back(triPoly);

	scene->Lines().push_back(
		Line2D(
			Vertex2D(Vector2D(0, 0), Color::Red),
			Vertex2D(Vector2D(300, 0), Color::Green),
			Frame2D(Vector2D(100, 100))
		)
	);
}

double scale = 1.0;
double angle = 0.0;

void Update(
	InputState inputState, 
	double delta)
{
	double speed = 10.0 * delta;

	if (inputState.up)
	{
		scene->Sprites()[0].Transform().Translation().Y(
			scene->Sprites()[0].Transform().Translation().Y() - speed
		);
	}
	if (inputState.down)
	{
		scene->Sprites()[0].Transform().Translation().Y(
			scene->Sprites()[0].Transform().Translation().Y() + speed
		);
	}
	if (inputState.left)
	{
		scene->Sprites()[0].Transform().Translation().X(
			scene->Sprites()[0].Transform().Translation().X() - speed
		);
	}
	if (inputState.right)
	{
		scene->Sprites()[0].Transform().Translation().X(
			scene->Sprites()[0].Transform().Translation().X() + speed
		);
	}
	if (inputState.in)
	{
		scale += 0.1 * delta;
		scene->Sprites()[0].Transform().Scale(scale);
	}
	if (inputState.out)
	{
		scale -= 0.1 * delta;
		scene->Sprites()[0].Transform().Scale(scale);
	}
	if (inputState.rotR)
	{
		angle += 2.0 * delta;
		scene->Sprites()[0].Transform().Angle(angle);
	}
	if (inputState.rotL)
	{
		angle -= 2.0 * delta;
		scene->Sprites()[0].Transform().Angle(angle);
	}
}
