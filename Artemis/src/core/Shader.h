#pragma once

#include <string>
#include <fstream>

#include <src/core/Common.h>

#include <GL/glew.h>

class Shader 
{
private:
	std::string m_ShaderSource;

	unsigned int m_ShaderID;

	int readShaderSource(std::string path);
public:
	enum class ShaderType {
		Fragment,
		Vertex
	};

	Shader(std::string shaderFilePath, Shader::ShaderType);
	bool Compile();

	unsigned int getShader() const 
	{
		return m_ShaderID;
	}
};