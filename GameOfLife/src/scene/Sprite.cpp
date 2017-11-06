#include "Sprite.h"

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	this->m_Position = position;
	this->m_Color = color;
	this->m_Size = size;
}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const Color& color)
{
	this->m_Position = position;
	this->m_Color = glm::vec4(color.r, color.g, color.b, color.a);
	this->m_Size = size;
}

Sprite::~Sprite()
{

}