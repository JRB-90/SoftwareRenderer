#include "MathUtils.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace softengine;

double MathUtils::ToRad(double deg)
{
	return (deg * M_PI) / 180.0;
}

double MathUtils::ToDeg(double rad)
{
	return (rad * 180.0) / M_PI;
}
