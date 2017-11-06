#pragma once

#include <GL/glew.h>
#include <src/core/Common.h>

class IndexBuffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_Components;

public:
	IndexBuffer();
	IndexBuffer(unsigned int* data, uint32_t componentCount);

	void Generate();
	void setData(unsigned int* data);
	void setComponentCount(uint32_t componentCount) { this->m_Components = componentCount; }

	inline void Bind() const { GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID)); }
	inline void Unbind() const { GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); };

	inline void Free() { GL(glDeleteBuffers(1, &this->m_BufferID)); }

	~IndexBuffer();
};