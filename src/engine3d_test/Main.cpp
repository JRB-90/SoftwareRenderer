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
			90.0,
			0.001,
			10000.0
		);
	camera->Position(Frame3D(Vector3D(0, 0, 200.0)));

	renderingEngine =
		std::make_shared<RenderingEngine3D>(
			scene,
			camera,
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
	ResourceLoader imageLoader;
	Texture catTexture = imageLoader.LoadImageResource("sprites\\cat.png");
	Texture brickTexture = imageLoader.LoadImageResource("textures\\brick.png");
	Texture nullTexture;

	std::vector<size_t> indices =
	{
		0, 1, 2
	};

	std::vector<Vertex3D> vertices =
	{
		Vertex3D(Vector3D(0.0, -100.0, 0.0), Vector2D(0.5, 0), Color::Red),
		Vertex3D(Vector3D(100.0, 100.0, 0.0), Vector2D(1.0, 1.0), Color::Green),
		Vertex3D(Vector3D(-100.0, 100.0, 0.0), Vector2D(0, 1.0), Color::Blue)
	};

	scene->Meshes().push_back(
		Mesh3D(
			indices,
			vertices,
			Frame3D(
				Vector3D(0, 0, 0),
				Rotation3D()
			),
			brickTexture,
			DrawType::Triangles
		)
	);

	//std::vector<size_t> indicesSq =
	//{
	//	0, 1, 2, 1, 3, 2
	//};

	//std::vector<Vertex3D> verticesSq =
	//{
	//	Vertex3D(Vector3D(-180.0, -180.0, 0.0), Vector2D(0, 0), Color::White),
	//	Vertex3D(Vector3D(180.0, -180.0, 0.0), Vector2D(1, 0), Color::White),
	//	Vertex3D(Vector3D(-180.0, 180.0, 0.0), Vector2D(0, 1), Color::White),
	//	Vertex3D(Vector3D(180.0, 180.0, 0.0), Vector2D(1, 1), Color::White)
	//};

	//scene->Meshes().push_back(
	//	Mesh3D(
	//		indicesSq,
	//		verticesSq,
	//		Frame3D(
	//			Vector3D(0, 0, 1.0),
	//			Rotation3D()
	//		),
	//		catTexture,
	//		DrawType::Triangles
	//	)
	//);
}

double speed = 20.0;

void Update(
	InputState inputState,
	double delta)
{
	if (inputState.up)
	{
		camera->Position().Translation().Z(
			camera->Position().Translation().Z() - speed
		);
	}
	if (inputState.down)
	{
		camera->Position().Translation().Z(
			camera->Position().Translation().Z() + speed
		);
	}
	if (inputState.left)
	{
		camera->Position().Translation().X(
			camera->Position().Translation().X() - speed
		);
	}
	if (inputState.right)
	{
		camera->Position().Translation().X(
			camera->Position().Translation().X() + speed
		);
	}
	if (inputState.in)
	{
		camera->Position().Translation().Y(
			camera->Position().Translation().Y() + speed
		);
	}
	if (inputState.out)
	{
		camera->Position().Translation().Y(
			camera->Position().Translation().Y() - speed
		);
	}
	if (inputState.rotR)
	{
		camera->Position().Rotation().Ry(
			camera->Position().Rotation().Ry() - (speed / 10.0)
		);
	}
	if (inputState.rotL)
	{
		camera->Position().Rotation().Ry(
			camera->Position().Rotation().Ry() + (speed / 10.0)
		);
	}
}
