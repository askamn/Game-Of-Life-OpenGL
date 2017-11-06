#pragma once

#include <vector>

#include <GL/glew.h>
#include <src/core/Common.h>
#include <src/core/Buffer.h>

class VertexArray
{
private:
	unsigned int m_vaoID;
	std::vector<Buffer*> m_Buffers;

public:
	VertexArray();

	// Binds the vertex array or unbinds them
	inline void Bind()		const { glBindVertexArray(this->m_vaoID); }
	inline void Unbind()	const { glBindVertexArray(0); }
	
	// Add a new buffer to this vertex array such as the position buffer or the color buffer.
	void AddBuffer(Buffer* buffer, unsigned int index);

	inline void Free() const { glDeleteVertexArrays(1, &this->m_vaoID); }

	~VertexArray();
};