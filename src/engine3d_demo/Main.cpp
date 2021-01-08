#include "Engine.h"
#include "RenderingEngine3D.h"
#include "Scene3D.h"
#include "Camera.h"
#include "MeshBuilder.h"
#include "Material.h"
#include "ResourceLoader.h"
#include "Texture.h"
#include "Color.h"
#include "ModelImporter.h"
#include "Vector3D.h"

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

double speed = 1.0;
double timeInc = 0;
bool isSpinning = false;
Vector3D point1Pos(5, 5, 0);
Vector3D point2Pos(0, 5, 5);
Color point1Col(1.0, 0.0, 0.0, 1.0);
Color point2Col(0.0, 0.0, 1.0, 1.0);
std::shared_ptr<Texture> brickTexture;

void SetupScene();
void Update(
	InputState inputState,
	double delta
);
void UpdateInput(
	InputState inputState,
	double delta
);
void UpdateModels(
	InputState inputState,
	double delta
);

int main(int argc, const char* argv[])
{
	std::cout << "Starting..." << std::endl;

	//if (putenv("OMP_WAIT_POLICY=passive"))
	//{
	//	std::cerr << "Failed to set OMP_WAIT_POLICY to passive" << std::endl;
	//}

	std::srand(std::time(nullptr));
	scene = std::make_shared<Scene3D>();
	ResourceLoader imageLoader;
	brickTexture = std::make_shared<Texture>(
		imageLoader.LoadImageResource("textures\\brick.png")
	);
	SetupScene();

	camera =
		std::make_shared<Camera>(
			PIXELS_WIDTH,
			PIXELS_HEIGHT,
			60.0,
			0.1,
			10000.0
			);
	camera->Position(Frame3D(Vector3D(1.3, 0.5, 4.0)));

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
	Mesh3D point1Mesh = ModelImporter::LoadModelResource(
		"models/sphere.obj",
		Material(point1Col, ShadingType::None),
		true, false
	);

	Mesh3D point2Mesh = ModelImporter::LoadModelResource(
		"models/sphere.obj",
		Material(point2Col, ShadingType::None),
		true, false
	);

	//scene->Meshes().push_back(point1Mesh);
	//scene->Meshes().push_back(point2Mesh);

	//Mesh3D monkeyMesh = ModelImporter::LoadModelResource(
	//	"models/suzanne.obj",
	//	Material(Color(0.5, 0.5, 0.5, 1.0), ShadingType::Phong),
	//	true, false
	//);
	Mesh3D monkeyMesh = ModelImporter::LoadModelResource(
		"models/suzanne.obj",
		Material(*brickTexture, ShadingType::Phong),
		true, false
	);
	monkeyMesh.Transform().Translation(Vector3D(0, 0, 0));
	scene->Meshes().push_back(monkeyMesh);

	//scene->Meshes().push_back(
	//	MeshBuilder::BuildPlane(
	//		2.0,
	//		2.0,
	//		Material(brickTexture, ShadingType::None)
	//	)
	//);

	AmbientLight ambient(
		Color::White,
		0.25
	);
	DirectionalLight directional(
		Vector3D(-1, -1, -1),
		Color(Color::White)
	);
	PointLight point1(
		point1Pos,
		point1Col,
		Attenuation()
	);
	PointLight point2(
		point2Pos,
		point2Col,
		Attenuation()
	);

	scene->Lighting().SetAmbientLight(ambient);
	scene->Lighting().GetDirectionalLights().push_back(directional);
	scene->Lighting().GetPointsLights().push_back(point1);
	scene->Lighting().GetPointsLights().push_back(point2);
}

void Update(
	InputState inputState,
	double delta)
{
	UpdateInput(
		inputState,
		delta
	);

	UpdateModels(
		inputState,
		delta
	);

	camera->LookAt(Vector3D(), Vector3D(0, 1, 0));
	timeInc += 10.0;
}

void UpdateInput(
	InputState inputState,
	double delta)
{
	double moveDelta = speed * delta;

	if (inputState.up)
	{
		camera->RotateAboutPoint(Vector3D(), Rotation3D(-moveDelta, 0.0, 0.0), Vector3D(0, 1, 0));
	}
	if (inputState.down)
	{
		camera->RotateAboutPoint(Vector3D(), Rotation3D(moveDelta, 0.0, 0.0), Vector3D(0, 1, 0));
	}
	if (inputState.left)
	{
		camera->RotateAboutPoint(Vector3D(), Rotation3D(0.0, -moveDelta, 0.0), Vector3D(0, 1, 0));
	}
	if (inputState.right)
	{
		camera->RotateAboutPoint(Vector3D(), Rotation3D(0.0, moveDelta, 0.0), Vector3D(0, 1, 0));
	}
	if (inputState.in)
	{
		camera->Position(camera->Position() * Frame3D(Vector3D(0.0, 0.0, moveDelta)));
	}
	if (inputState.out)
	{
		camera->Position(camera->Position() * Frame3D(Vector3D(0.0, 0.0, -moveDelta)));
	}

	if (inputState.stopSpin)
	{
		isSpinning = false;
	}
	if (inputState.startSpin)
	{
		isSpinning = true;
	}

	if (inputState.noShading)
	{
		scene->Meshes()[2].GetMaterial().SetShadingType(ShadingType::None);
	}
	if (inputState.normalShading)
	{
		scene->Meshes()[2].GetMaterial().SetShadingType(ShadingType::Normal);
	}
	if (inputState.flatShading)
	{
		scene->Meshes()[2].GetMaterial().SetShadingType(ShadingType::Flat);
	}
	if (inputState.phongShading)
	{
		scene->Meshes()[2].GetMaterial().SetShadingType(ShadingType::Phong);
	}

	if (inputState.wireFrameModeOff)
	{
		renderingEngine->GetPipelineConfiguration().wireframeModeEnabled = false;
	}
	if (inputState.wireFrameModeOn)
	{
		renderingEngine->GetPipelineConfiguration().wireframeModeEnabled = true;
	}

	if (inputState.noCulling)
	{
		renderingEngine->GetPipelineConfiguration().backFaceCullingMode = BackFaceCullingMode::NoCulling;
	}
	if (inputState.cwCulling)
	{
		renderingEngine->GetPipelineConfiguration().backFaceCullingMode = BackFaceCullingMode::Clockwise;
	}
	if (inputState.acwCulling)
	{
		renderingEngine->GetPipelineConfiguration().backFaceCullingMode = BackFaceCullingMode::AntiClockwise;
	}

	if (inputState.noDepthCheck)
	{
		renderingEngine->GetPipelineConfiguration().depthCheckMode = DepthCheckMode::NoDepthCheck;
	}
	if (inputState.lessThanDepthCheck)
	{
		renderingEngine->GetPipelineConfiguration().depthCheckMode = DepthCheckMode::DepthCheckLessThan;
	}
	if (inputState.moreThanDepthCheck)
	{
		renderingEngine->GetPipelineConfiguration().depthCheckMode = DepthCheckMode::DepthCheckGreaterThan;
	}

	if (inputState.noTexture)
	{
		scene->Meshes()[2].GetMaterial().SetTexture(Texture());
	}
	if (inputState.texture)
	{
		scene->Meshes()[2].GetMaterial().SetTexture(*brickTexture);
	}
}

void UpdateModels(
	InputState inputState,
	double delta)
{
	double moveDelta = speed * delta;
	double ts = std::sin(timeInc / 180);
	double tc = std::cos(timeInc / 180);

	point1Pos = Vector3D(ts * 3.0, point1Pos.Y(), point1Pos.Z());
	point2Pos = Vector3D(point2Pos.X(), point2Pos.Y(), tc * 5.0);
	//scene->Meshes()[0].Transform().Translation(point1Pos);
	//scene->Meshes()[1].Transform().Translation(point2Pos);
	scene->Lighting().GetPointsLights()[0].Position(point1Pos);
	scene->Lighting().GetPointsLights()[1].Position(point2Pos);

	if (isSpinning)
	{
		//scene->Meshes()[2].Transform(scene->Meshes()[2].Transform() * Frame3D(Rotation3D(0, moveDelta, 0)));
	}
}
