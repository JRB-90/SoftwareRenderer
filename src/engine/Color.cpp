#include "Color.h"
#include "MathUtils.h"
#include <algorithm>

using namespace softengine;

const Color Color::Black	= Color(0.0, 0.0, 0.0, 1.0);
const Color Color::White	= Color(1.0, 1.0, 1.0, 1.0);
const Color Color::Red		= Color(1.0, 0.0, 0.0, 1.0);
const Color Color::Green	= Color(0.0, 1.0, 0.0, 1.0);
const Color Color::Blue		= Color(0.0, 0.0, 1.0, 1.0);
const Color Color::Yellow	= Color(1.0, 1.0, 0.0, 1.0);
const Color Color::Magenta	= Color(1.0, 0.0, 1.0, 1.0);
const Color Color::Cyan		= Color(0.0, 1.0, 1.0, 1.0);

Color::Color()
  :
	color(Color::Black.GetAs4D())
{
}

Color::Color(const Color& color)
  :
	color(color.GetAs4D())
{
}

Color::Color(Color4B& color)
  :
	color(
		Color4D(
			ToColorDouble(color.r),
			ToColorDouble(color.g),
			ToColorDouble(color.b),
			ToColorDouble(color.a)
		)
	)
{
}

Color::Color(Color4D& color)
  :
	color(color)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  :
	color(
		Color4D(
			ToColorDouble(r),
			ToColorDouble(g),
			ToColorDouble(b),
			ToColorDouble(a)
		)
	)
{
}

Color::Color(double r, double g, double b, double a)
  :
	color(
		Color4D(
			r,
			g,
			b,
			a
		)
	)
{
}

Color4B Color::GetAs4B() const
{
	return 
		Color4B(
			ToColorByte(color.r),
			ToColorByte(color.g),
			ToColorByte(color.b),
			ToColorByte(color.a)
		);
}

Color4D Color::GetAs4D() const
{
	return color;
}

Color Color::operator+(const Color& vec)
{
	return
		Color(
			std::max(std::min(color.r + color.r, 1.0), 0.0),
			std::max(std::min(color.g + color.g, 1.0), 0.0),
			std::max(std::min(color.b + color.b, 1.0), 0.0),
			std::max(std::min(color.a + color.a, 1.0), 0.0)
		);
}

Color Color::operator-(const Color& vec)
{
	return
		Color(
			std::max(std::min((color.r - color.r) * 2.0, 1.0), 0.0),
			std::max(std::min((color.g - color.g) * 2.0, 1.0), 0.0),
			std::max(std::min((color.b - color.b) * 2.0, 1.0), 0.0),
			std::max(std::min((color.a - color.a) * 2.0, 1.0), 0.0)
		);
}

Color Color::operator*(const double scalar)
{
	return
		Color(
			std::max(std::min(color.r * scalar, 1.0), 0.0),
			std::max(std::min(color.g * scalar, 1.0), 0.0),
			std::max(std::min(color.b * scalar, 1.0), 0.0),
			std::max(std::min(color.a * scalar, 1.0), 0.0)
		);
}

Color Color::operator/(const double scalar)
{
	return
		Color(
			std::max(std::min(color.r / scalar, 1.0), 0.0),
			std::max(std::min(color.g / scalar, 1.0), 0.0),
			std::max(std::min(color.b / scalar, 1.0), 0.0),
			std::max(std::min(color.a / scalar, 1.0), 0.0)
		);
}

uint8_t Color::ToColorByte(double val) const
{
	return (uint8_t)(255.0 * val);
}

double Color::ToColorDouble(uint8_t val) const
{
	return ((double)val / 255.0);
}

Color Color::InterpolateColor(
	Color& c1,
	Color& c2,
	double factor)
{
	Color4D c1d = c1.GetAs4D();
	Color4D c2d = c2.GetAs4D();

	return
		Color(
			MathUtils::Interpolate(c1d.r, c2d.r, factor),
			MathUtils::Interpolate(c1d.g, c2d.g, factor),
			MathUtils::Interpolate(c1d.b, c2d.b, factor),
			MathUtils::Interpolate(c1d.a, c2d.a, factor)
		);
}
