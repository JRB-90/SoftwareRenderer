#include "Engine.h"
#include "RenderingEngine3D.h"
#include "Scene3D.h"
#include "Camera.h"
#include "Material.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"

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
	camera->Position(Frame3D(Vector3D(0, 0, 350.0)));

	renderingEngine =
		std::make_shared<RenderingEngine3D>(
			scene,
			camera,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
		);
	renderingEngine->RefreshColor(Color(0.3, 0.3, 0.3, 1.0));

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

	scene->Meshes().push_back(
		MeshBuilder::BuildCube(
			100.0,
			100.0,
			100.0,
			//Material(brickTexture, ShadingType::Flat),
			//false
			Material(Color(Color::Red), ShadingType::Phong),
			true
		)
	);

	//scene->Meshes().push_back(
	//	MeshBuilder::BuildFrame(
	//		100.0,
	//		Frame3D(Vector3D(0, 0, 0))
	//	)
	//);

	AmbientLight ambient(
		Color::White,
		0.25
	);
	DirectionalLight directional(
		Vector3D(0, 0, 1),
		Color::Blue
	);
	
	scene->Lighting().SetAmbientLight(ambient);
	scene->Lighting().GetDirectionalLights().push_back(directional);
}

double modelSpeed = 3.0;
double speed = 10.0;

void Update(
	InputState inputState,
	double delta)
{
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
		camMove = camMove * Frame3D(Rotation3D(0, -moveDelta / 10.0, 0));
	}
	if (inputState.rotL)
	{
		camMove = camMove * Frame3D(Rotation3D(0, moveDelta / 10.0, 0));
	}

	camera->Position(camera->Position() * camMove);

	scene->Meshes()[0].Transform(
		scene->Meshes()[0].Transform() * Rotation3D((-modelSpeed * delta) / 3.0, (modelSpeed * delta) / 3.0, 0.0)
	);

	//scene->Meshes()[0].Transform(
	//	scene->Meshes()[0].Transform() * Frame3D(Vector3D(0.0, 0.0, speed))
	//);
}
