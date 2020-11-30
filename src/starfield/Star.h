#pragma once

#include "Point2D.h"
#include "Vector2D.h"

namespace starfield
{
	class Star
	{
	public:
		Star();
		Star(
			softengine::Point2D position,
			softengine::Vector2D direction,
			double speed
		);

		softengine::Point2D& Position() { return position; }
		softengine::Vector2D& Direction() { return direction; }
		double Speed() const { return speed; }
		void Speed(double speed) { this->speed = speed; }
		void Move();

	private:
		softengine::Point2D position;
		softengine::Vector2D direction;
		double speed;
	};
}