#pragma once

#include <src/core/Common.h>
#include <src/core/Color.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

class Sprite 
{
private:
	// Position of the center of the sprite
	glm::vec3 m_Position;

	// Color of this sprite
	glm::vec4 m_Color;

	// Size of this sprite, width x height
	glm::vec2 m_Size;

public:
	Sprite() = default;
	Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	Sprite(const glm::vec3& position, const glm::vec2& size, const Color& color);

	void setPosition(const glm::vec3& position) { this->m_Position = position; }
	void setColor(const glm::vec4& color)		{ this->m_Color = color; }
	void setSize(const glm::vec2& size)			{ this->m_Size = size; }

	inline glm::vec2 getSize() const			{ return this->m_Size; }
	inline glm::vec3 getPosition() const		{ return this->m_Position; }
	inline glm::vec4 getColor() const			{ return this->m_Color; }

	~Sprite();
};
