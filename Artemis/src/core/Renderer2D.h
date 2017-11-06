#pragma once

#include <vector>

#include <src/scene/Sprite.h>
#include <src/core/Common.h>

#include <src/core/VertexArray.h>
#include <src/core/Buffer.h>
#include <src/core/IndexBuffer.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#define MAX_SPRITES					60000
#define VERTEX_LAYOUT_POSITION		0
#define VERTEX_LAYOUT_COLOR			1

struct VertexLayout
{
	glm::vec3 position;
	glm::vec4 color;
};

class Renderer2D
{
private:
	std::vector<Sprite*> m_Sprites;
	std::vector<uint32_t> m_Indices;
	
	uint32_t m_VBO;
	uint32_t m_EBO;
	uint32_t m_VAO;
	uint32_t m_IndexCount;

	VertexLayout* m_Buffer;

public:
	Renderer2D();

	// Generates a new VBO, EBO and a corresponding VAO
	void Begin();

	// This sends the data stored on the client side to the GPU buffers
	void End();

	// Renders the sprites
	void Render();

	// Adds a new sprite to be batch-rendered
	void AddSprite(Sprite* sprite);
	void AddSprites(const std::vector<Sprite*>& sprites);

	// Return the sprite batch
	std::vector<Sprite*> GetSpriteBatch() const { return this->m_Sprites; };

	~Renderer2D();
};