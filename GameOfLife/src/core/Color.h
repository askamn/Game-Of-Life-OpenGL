#pragma once

#include <random>

#include <src/core/Common.h>

#include <glm/glm.hpp>
#include <glm/vec4.hpp>

#define COLOR_NUM_INTERNAL_COLORS 25

class Color
{
private:
	// For Randomizing
	static std::random_device _randomDevice;
	static std::mt19937 _mt;
	static std::uniform_int_distribution<int> _number;

public:
	float r;
	float g;
	float b;
	float a;

	static uint32_t m_Colors[];

	Color();
	Color(uint32_t color);
	Color(int r, int g, int b, int a);
	Color(const glm::vec4& color, bool normalize = true);

	static Color Random();

	void normalize();

	const Color& operator=(const glm::vec4& color)
	{
		return Color(color.r, color.g, color.b, color.a);
	}

	~Color();
};