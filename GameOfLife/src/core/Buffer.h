#pragma once

#include <vector>

#include <GL/glew.h>
#include <src/core/Common.h>

class Buffer
{
private:
	uint32_t		m_BufferID;
	uint32_t		m_BufferUsage;
	uint32_t		m_numElements;
	uint8_t			m_componentsPerVertex;

public:
	Buffer();

	// Generic Constructor
	Buffer(float* data, uint32_t numElements, uint8_t componentsPerVertex, uint32_t usage = GL_STATIC_DRAW);

	// Buffer constructor that allows you to set the usage type of this buffer
	Buffer(std::vector<float> data, uint8_t componentsPerVertex, uint32_t usage = GL_STATIC_DRAW);

	// Generates a buffer
	void Generate();

	// Sets the data of this buffer
	void setData(float* data);

	// Sets the number of elements that are stored in this buffer
	void setNumElements(uint32_t numElements)		{ this->m_numElements = numElements; }

	// Number of components 
	void setComponentCount(uint8_t componentCount)	{ this->m_componentsPerVertex = componentCount; }

	// Sets the buffer usage
	void setUsage(uint32_t usage)					{ this->m_BufferUsage = usage; }

	// Binds the buffer
	inline void Bind()					const { GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID)); };

	// Unbinds the buffer
	inline void Unbind()				const { GL(glBindBuffer(GL_ARRAY_BUFFER, 0)); };

	unsigned int getBuffer()			const { return this->m_BufferID; }
	unsigned int getNumElements()		const { return this->m_numElements; }
	unsigned int getComponentCount()	const { return this->m_componentsPerVertex; }

	// Free's the buffer
	inline void Free()					{ GL(glDeleteBuffers(1, &this->m_BufferID)); }

	~Buffer();
};