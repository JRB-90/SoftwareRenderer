#include "Engine.h"
#include "IRenderingEngine.h"
#include "RenderingEngine2D.h"
#include "RenderingWindow.h"
#include "RenderingMode.h"
#include "IScene.h"
#include "Scene2D.h"
#include "Point2D.h"
#include "Color.h"
#include "Star.h"
#include "InputState.h"

#include <iostream>
#include <memory>
#include <random>
#include <ctime>
#include <vector>

using namespace softengine;
using namespace starfield;

const size_t NUM_STARS = 100;
const size_t WINDOW_WIDTH = 640;
const size_t WINDOW_HEIGHT = 480;
const size_t PIXELS_WIDTH = 960;
const size_t PIXELS_HEIGHT = 540;
const int UPDATE_RATE = 30;

std::shared_ptr<Scene2D> scene;
std::vector<Star> stars;

void SetupScene();
void Update(
	InputState inputstate,
	double delta
);

int main(int argc, const char* argv[])
{
	std::srand(std::time(nullptr));
	scene = std::make_shared<Scene2D>();
	SetupScene();

	std::shared_ptr<IRenderingEngine> renderingEngine =
		std::make_shared<RenderingEngine2D>(
			scene,
			PIXELS_WIDTH,
			PIXELS_HEIGHT
			);

	scene->Lines().push_back(
		Line2D(
			Vector2D(),
			Vector2D()
		)
	);

	Engine engine(
		renderingEngine,
		RenderingMode::Software,
		"Starfield",
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		UPDATE_RATE,
		true
	);

	engine.RegisterUpdateCallback(Update);
	engine.Run();

	return 0;
}

void SetupScene()
{
	for (size_t i = 0; i < NUM_STARS; i++)
	{
		Star s(
			Point2D(
				Vertex2D(
					Vector2D(
						PIXELS_WIDTH / 2,
						PIXELS_HEIGHT / 2
					),
					Color::White
				)
			),
			Vector2D(
				((double)std::rand() / (RAND_MAX / 2) - 1.0),
				((double)std::rand() / (RAND_MAX / 2) - 1.0)
			).Normalised(),
			0.01
		);
		stars.push_back(s);
		scene->Points().push_back(stars[i].Position());
	}
}

void Update(
	InputState inputstate,
	double delta)
{
	for (Star& s : stars)
	{
		s.Move();
		if (s.Position().Vertex().Position.X() > (PIXELS_WIDTH) ||
			s.Position().Vertex().Position.X() < 0.0 ||
			s.Position().Vertex().Position.Y() > (PIXELS_HEIGHT) ||
			s.Position().Vertex().Position.Y() < 0.0)
		{
			s.Position().Vertex().Position.X(PIXELS_WIDTH / 2.0);
			s.Position().Vertex().Position.Y(PIXELS_HEIGHT / 2.0);
			s.Direction().X(((double)std::rand() / (RAND_MAX / 2) - 1.0));
			s.Direction().Y(((double)std::rand() / (RAND_MAX / 2) - 1.0));
			s.Speed(0.01);
		}

		Vector2D displacement = 
			s.Position().Vertex().Position -
			Vector2D(PIXELS_WIDTH / 2, PIXELS_HEIGHT / 2);
		s.Speed(s.Speed() + displacement.Length() * 0.01 * delta);
	}

	for (size_t i = 0; i < scene->Points().size(); i++)
	{
		scene->Points()[i].Vertex().Position.X(stars[i].Position().Vertex().Position.X());
		scene->Points()[i].Vertex().Position.Y(stars[i].Position().Vertex().Position.Y());
	}
}
