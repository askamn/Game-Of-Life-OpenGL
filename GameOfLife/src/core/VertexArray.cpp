#include "VertexArray.h"

VertexArray::VertexArray()
{
	GL(glGenVertexArrays(1, &this->m_vaoID));
}

void VertexArray::AddBuffer(Buffer* buffer, unsigned int index)
{
	this->m_Buffers.emplace_back(buffer);
	this->Bind();
	buffer->Bind();

	GL(glEnableVertexAttribArray(index));
	GL(glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0)));

	buffer->Unbind();
	this->Unbind();
}

VertexArray::~VertexArray()
{
	for (const auto& buffer : this->m_Buffers)
	{
		buffer->Free();
		delete buffer;
	}

	GL(glDeleteVertexArrays(1, &this->m_vaoID));
}