#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	//GL(glGenBuffers(1, &this->m_BufferID));
}

void IndexBuffer::Generate()
{
	GL(glGenBuffers(1, &this->m_BufferID));
}

void IndexBuffer::setData(unsigned int* data)
{
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Components, data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(unsigned int* data, uint32_t componentCount)
	: m_Components(componentCount)
{
	GL(glGenBuffers(1, &this->m_BufferID));
	this->Bind();
	this->setData(data);
}

IndexBuffer::~IndexBuffer()
{

}