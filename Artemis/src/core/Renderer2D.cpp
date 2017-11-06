#include "Renderer2D.h"

Renderer2D::Renderer2D() :
	m_IndexCount(0),
	m_Buffer(nullptr),
	m_VBO(0),
	m_EBO(0),
	m_VAO(0)
{
	// Reserve the index count in advance
	this->m_Indices.reserve(MAX_SPRITES * 6);
	this->m_Indices.resize(MAX_SPRITES * 6);

	uint32_t offset = 0;
	for (int i = 0; i < MAX_SPRITES; i += 6)
	{
		this->m_Indices[  i  ] = offset + 0;
		this->m_Indices[i + 1] = offset + 1;
		this->m_Indices[i + 2] = offset + 2;

		this->m_Indices[i + 3] = offset + 2;
		this->m_Indices[i + 4] = offset + 3;
		this->m_Indices[i + 5] = offset + 0;

		offset += 4;
	}

	GL(glGenVertexArrays(1, &this->m_VAO));
	GL(glGenBuffers(1, &this->m_VBO));
	GL(glGenBuffers(1, &this->m_EBO));

	GL(glBindVertexArray(this->m_VAO));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * this->m_Indices.size(), &this->m_Indices[0], GL_DYNAMIC_DRAW));

	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));

	GL(glEnableVertexAttribArray(VERTEX_LAYOUT_POSITION));
	GL(glEnableVertexAttribArray(VERTEX_LAYOUT_COLOR));

	GL(glVertexAttribPointer(VERTEX_LAYOUT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), reinterpret_cast<void*>(0)));
	GL(glVertexAttribPointer(VERTEX_LAYOUT_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), reinterpret_cast<void*>(offsetof(VertexLayout, VertexLayout::color))));

	GL(glBindVertexArray(0));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
}

void Renderer2D::AddSprite(Sprite* sprite)
{
	this->m_Sprites.push_back(sprite);
	this->m_IndexCount += 6;
}

void Renderer2D::AddSprites(const std::vector<Sprite*>& sprites)
{
	for (const auto& sprite : sprites)
	{
		this->m_Sprites.push_back(sprite);
		this->m_IndexCount += 6;
	}
}

void Renderer2D::Begin()
{
	GL(glBindVertexArray(this->m_VAO));
}

void Renderer2D::End()
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(VertexLayout) * 4 * this->m_Sprites.size(), NULL, GL_DYNAMIC_DRAW));

	this->m_Buffer = (VertexLayout*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	for (const auto& sprite : this->m_Sprites)
	{
		glm::vec3 position = sprite->getPosition();
		glm::vec4 color = sprite->getColor();
		glm::vec2 size = sprite->getSize();

		this->m_Buffer->position = glm::vec3(position.x - size.x / 2.0f, position.y - size.y / 2.0f, 0.0f);
		this->m_Buffer->color = color;
		this->m_Buffer++;

		this->m_Buffer->position = glm::vec3(position.x + size.x / 2.0f, position.y - size.y / 2.0f, 0.0f);
		this->m_Buffer->color = color;
		this->m_Buffer++;

		this->m_Buffer->position = glm::vec3(position.x + size.x / 2.0f, position.y + size.y / 2.0f, 0.0f);
		this->m_Buffer->color = color;
		this->m_Buffer++;

		this->m_Buffer->position = glm::vec3(position.x - size.x / 2.0f, position.y + size.y / 2.0f, 0.0f);
		this->m_Buffer->color = color;
		this->m_Buffer++;
	}

	GL(glUnmapBuffer(GL_ARRAY_BUFFER));

	glBindVertexArray(0);
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

	this->m_Sprites.clear();
}

void Renderer2D::Render()
{
	glBindVertexArray(this->m_VAO);
	GL(glDrawElements(GL_TRIANGLES, this->m_IndexCount, GL_UNSIGNED_INT, 0));
	glBindVertexArray(0);

	// Reset the index count
	this->m_IndexCount = 0;
}

Renderer2D::~Renderer2D()
{
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_EBO);
	glDeleteVertexArrays(1, &this->m_VAO);

	this->m_Indices.clear();
	this->m_Buffer = nullptr;

	for (const auto& sprite : this->m_Sprites)
	{
		if (sprite)
		{
			delete sprite;
		}
	}

	this->m_Sprites.clear();
}