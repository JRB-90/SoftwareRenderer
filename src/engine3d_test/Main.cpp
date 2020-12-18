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
	InputState inputState,
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
	std::vector<size_t> indices =
	{
		0, 1, 2
	};

	std::vector<Vertex3D> vertices =
	{
		Vertex3D(Vector3D(0.0, -100.0, 0.0), Color::Red),
		Vertex3D(Vector3D(100.0, 100.0, 0.0), Color::Green),
		Vertex3D(Vector3D(-100.0, 100.0, 0.0), Color::Blue)
	};

	scene->Meshes().push_back(
		Mesh3D(
			indices,
			vertices,
			DrawType::Triangles,
			Frame3D(
				Vector3D(PIXELS_WIDTH / 2, PIXELS_HEIGHT / 2, 0),
				Rotation3D()
			)
		)
	);

	std::vector<size_t> indicesSq =
	{
		0, 1, 2
	};

	std::vector<Vertex3D> verticesSq =
	{
		Vertex3D(Vector3D(-180.0, -180.0, 0.0), Color::White),
		Vertex3D(Vector3D(180.0, -180.0, 0.0), Color::White),
		Vertex3D(Vector3D(-180.0, 180.0, 0.0), Color::White),
		Vertex3D(Vector3D(180.0, 180.0, 0.0), Color::White)
	};

	scene->Meshes().push_back(
		Mesh3D(
			indicesSq,
			verticesSq,
			DrawType::Triangles,
			Frame3D(
				Vector3D(PIXELS_WIDTH / 2, PIXELS_HEIGHT / 2, -1.0),
				Rotation3D()
			)
		)
	);
}

double speed = 2.0;

void Update(
	InputState inputState,
	double delta)
{
	if (inputState.up)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(-speed, 0.0, 0.0)
		);
	}
	if (inputState.down)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(speed, 0.0, 0.0)
		);
	}
	if (inputState.left)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(0.0, speed, 0.0)
		);
	}
	if (inputState.right)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(0.0, -speed, 0.0)
		);
	}
	if (inputState.rotR)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(0.0, 0.0, speed)
		);
	}
	if (inputState.rotL)
	{
		scene->Meshes()[0].Transform().Rotation(
			scene->Meshes()[0].Transform().Rotation() *
			Rotation3D(0.0, 0.0, -speed)
		);
	}
}
