#include "Shader.h"

Shader::Shader(std::string shaderSource, Shader::ShaderType shaderType)
{
	switch (shaderType)
	{
		case ShaderType::Fragment:
			this->m_ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case ShaderType::Vertex:
			this->m_ShaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
	}

	int length = this->readShaderSource(shaderSource);

	const char* source = this->m_ShaderSource.c_str();
	glShaderSource(this->m_ShaderID, 1, &source, &length);
	this->m_ShaderSource.clear();

	this->Compile();
}

bool Shader::Compile()
{
	glCompileShader(this->m_ShaderID);

	int status;

	glGetShaderiv(this->m_ShaderID, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetShaderiv(this->m_ShaderID, GL_INFO_LOG_LENGTH, &status);

		char* error = new char[status + 1];

		glGetShaderInfoLog(this->m_ShaderID, status + 1, &status, error);

		LOG_ERROR(error);
		return false;
	}

	return true;
}

int Shader::readShaderSource(std::string path)
{
	std::fstream shader(path, std::ios::in | std::ios::binary);

	if (!shader.good())
	{
		LOG_ERROR("Failed to open Shader file at location: " + path);
		return 0;
	}

	int length = 0;

	shader.seekg(0, std::ios::end);
	length = shader.tellg();
	shader.seekg(0, std::ios::beg);

	m_ShaderSource.reserve(length);

	shader.read(&m_ShaderSource[0], length);

	shader.close();

	return length;
}

