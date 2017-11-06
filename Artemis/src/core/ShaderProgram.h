#pragma once

#include <src/core/Common.h>
#include <src/core/Shader.h>
#include <GL/glew.h>

class ShaderProgram
{
private:
	unsigned int m_ProgramID;

public:
	ShaderProgram();

	inline void AttachShader(unsigned int shaderID)
	{
		glAttachShader(this->m_ProgramID, shaderID);
	}

	inline void AttachShader(Shader shader)
	{
		glAttachShader(this->m_ProgramID, shader.getShader());
	}

	inline void Use() const
	{
		glUseProgram(this->m_ProgramID);
	}

	inline void Unuse() const
	{
		glUseProgram(0);
	}

	inline uint32_t GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(this->m_ProgramID, name);
	}

	inline void SetUniform1f(const char* name, float x)
	{
		glUniform1f(this->GetUniformLocation(name), x);
	}

	inline void SetUniform2f(const char* name, float x, float y)
	{
		glUniform2f(this->GetUniformLocation(name), x, y);
	}

	inline void SetUniform3f(const char* name, float x, float y, float z)
	{
		glUniform3f(this->GetUniformLocation(name), x, y, z);
	}

	inline void SetUniform4f(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(this->GetUniformLocation(name), x, y, z, w);
	}

	inline void SetMatrix3f(const char* name, float* matrix, uint32_t numElements, uint8_t transpose = GL_FALSE)
	{
		glUniformMatrix3fv(this->GetUniformLocation(name), numElements, transpose, matrix);
	}

	inline void SetMatrix4f(const char* name, float* matrix, uint8_t transpose = GL_FALSE)
	{
		glUniformMatrix4fv(this->GetUniformLocation(name), 1, transpose, matrix);
	}

	bool Link();

	~ShaderProgram();
};