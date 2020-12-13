#pragma once

#include <cinttypes>

namespace softengine
{
	struct Color4B
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color4B(
			uint8_t r,
			uint8_t g,
			uint8_t b,
			uint8_t a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	struct Color4D
	{
		double r;
		double g;
		double b;
		double a;

		Color4D(
			double r,
			double g,
			double b,
			double a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	class Color
	{
	public:
		Color();
		Color(const Color& color);
		Color(Color4B& color);
		Color(Color4D& color);
		Color(
			uint8_t r,
			uint8_t g,
			uint8_t b,
			uint8_t a
		);
		Color(
			double r,
			double g,
			double b,
			double a
		);

		Color4B GetAs4B() const;
		Color4D GetAs4D() const;

		Color operator+(const Color& vec);
		Color operator-(const Color& vec);
		Color operator*(const double scalar);
		Color operator/(const double scalar);

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;

	private:
		Color4D color;

		uint8_t ToColorByte(double val) const;
		double ToColorDouble(uint8_t val) const;
	};
}