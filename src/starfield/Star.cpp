#include "Star.h"

using namespace starfield;
using namespace softengine;

Star::Star()
  :
	speed(0.0)
{
}

Star::Star(
	softengine::Point2D position, 
	softengine::Vector2D direction, 
	double speed)
  :
	position(position),
	direction(direction),
	speed(speed)
{
}

void Star::Move()
{
	Vector2D moveVec = direction * speed;
	position.Vertex().Position = position.Vertex().Position + moveVec;
}
