#include "Buffer.h"

Buffer::Buffer() :
	m_BufferUsage(GL_STATIC_DRAW)
{
	//glGenBuffers(1, &this->m_BufferID);
}

void Buffer::Generate()
{
	GL(glGenBuffers(1, &this->m_BufferID));
}

Buffer::Buffer(std::vector<float> data, uint8_t componentsPerVertex, uint32_t usage) : 
	m_componentsPerVertex(componentsPerVertex),
	m_numElements(data.size()),
	m_BufferUsage(GL_STATIC_DRAW)
{
	GL(glGenBuffers(1, &this->m_BufferID));

	this->Bind();
	this->setData(&data[0]);
}

Buffer::Buffer(float* data, uint32_t numElements, uint8_t componentsPerVertex, uint32_t usage) :
	m_componentsPerVertex(componentsPerVertex),
	m_numElements(numElements),
	m_BufferUsage(usage)
{
	GL(glGenBuffers(1, &this->m_BufferID));

	this->Bind();
	this->setData(data);
}

void Buffer::setData(float* data)
{
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->m_numElements, data, this->m_BufferUsage));
}

Buffer::~Buffer()
{
}