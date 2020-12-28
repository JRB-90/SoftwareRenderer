#include "Engine.h"
#include "RenderingEngine3D.h"
#include "Scene3D.h"
#include "Camera.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Utils.h"

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
			1000.0
		);
	//camera->Position(Frame3D(Vector3D(500, 500, 500)));
	camera->Position(Frame3D(Vector3D(2, 2, 2)));
	//camera->Position(Frame3D(Vector3D(0.333, 0.333, 0.333)));
	camera->LookAt(Vector3D(0, 0, 0), Vector3D(0, 1, 0));

	Utils::PrintMatrix(camera->ProjectionMatrix());
	Utils::PrintMatrix(camera->ViewMatrix());

	renderingEngine =
		std::make_shared<RenderingEngine3D>(
			scene,
			camera,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
		);
	//renderingEngine->RefreshColor(Color(0.3, 0.3, 0.3, 1.0));

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
	Texture skyboxTexture = imageLoader.LoadImageResource("textures\\skybox.png");
	Texture checkerboardTexture = imageLoader.LoadImageResource("textures\\checkerboard.png");
	Texture nullTexture;

	std::vector<size_t> pointndices = { 0, 1, 2, 3 };
	std::vector<Vertex3D> pointVertices =
	{
		Vertex3D(Vector3D(0, 0, 0), Color::White),
		Vertex3D(Vector3D(1, 0, 0), Color::Red),
		Vertex3D(Vector3D(0, 1, 0), Color::Green),
		Vertex3D(Vector3D(0, 0, 1), Color::Blue)
	};
	//scene->Meshes().push_back(Mesh3D(pointndices, pointVertices, Frame3D(), DrawType::Points, ShadingType::None));

	//std::vector<size_t> indices =
	//{
	//	0, 1, 2, 2, 3, 0
	//};

	//std::vector<Vertex3D> vertices =
	//{
	//	Vertex3D(Vector3D(-50.0, -50.0, -200.0), Vector2D(0, 0), Color::White),
	//	Vertex3D(Vector3D(50.0, -50.0, -200.0), Vector2D(1.0, 0), Color::Black),
	//	Vertex3D(Vector3D(50.0, 50.0, 0.0), Vector2D(1.0, 1.0), Color::White),
	//	Vertex3D(Vector3D(-50.0, 50.0, 0.0), Vector2D(0, 1.0), Color::Black)
	//};

	//scene->Meshes().push_back(
	//	Mesh3D(
	//		indices,
	//		vertices,
	//		Frame3D(
	//			Vector3D(0, 0, 0),
	//			Rotation3D()
	//		),
	//		checkerboardTexture,
	//		DrawType::Triangles
	//	)
	//);

	//scene->Meshes().push_back(
	//	MeshBuilder::BuildCube(
	//		100.0,
	//		100.0,
	//		100.0,
	//		skyboxTexture
	//	)
	//);

	scene->Meshes().push_back(
		MeshBuilder::BuildFrame(
			1.0,
			Frame3D(Vector3D(0, 0, 0))
		)
	);

	AmbientLight ambient(
		Color::White,
		0.5
	);
	DirectionalLight directional(
		Vector3D(-1, -1, -1),
		Color::Red
	);
	
	scene->Lighting().SetAmbientLight(ambient);
	scene->Lighting().GetDirectionalLights().push_back(directional);
}

double speed = 0.1;

void Update(
	InputState inputState,
	double delta)
{
	std::printf(
		"%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n", 
		camera->Position().Translation().X(), camera->Position().Translation().Y(), camera->Position().Translation().Z(),
		camera->Position().Rotation().Rx(), camera->Position().Rotation().Ry(), camera->Position().Rotation().Rz()
	);

	Frame3D camMove;
	double moveDelta = speed * delta;

	if (inputState.up)
	{
		camMove = camMove * Frame3D(Vector3D(0, 0, -moveDelta));
	}
	if (inputState.down)
	{
		camMove = camMove * Frame3D(Vector3D(0, 0, moveDelta));
	}
	if (inputState.left)
	{
		camMove = camMove * Frame3D(Vector3D(-moveDelta, 0, 0));
	}
	if (inputState.right)
	{
		camMove = camMove * Frame3D(Vector3D(moveDelta, 0, 0));
	}
	if (inputState.in)
	{
		camMove = camMove * Frame3D(Vector3D(0, -moveDelta, 0));
	}
	if (inputState.out)
	{
		camMove = camMove * Frame3D(Vector3D(0, moveDelta, 0));
	}
	if (inputState.rotR)
	{
		camMove = camMove * Frame3D(Rotation3D(0, 0, -moveDelta * 10));
	}
	if (inputState.rotL)
	{
		camMove = camMove * Frame3D(Rotation3D(0, 0, moveDelta * 10));
	}

	camera->Position(camera->Position() * camMove);

	//scene->Meshes()[0].Transform(
	//	scene->Meshes()[0].Transform() * Rotation3D((-speed * delta) / 3.0, (speed * delta) / 6.0, 0.0)
	//);

	//scene->Meshes()[0].Transform(
	//	scene->Meshes()[0].Transform() * Frame3D(Vector3D(0.0, 0.0, speed))
	//);
}
