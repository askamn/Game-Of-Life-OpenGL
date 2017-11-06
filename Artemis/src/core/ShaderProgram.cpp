#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->m_ProgramID = glCreateProgram();
}

bool ShaderProgram::Link()
{
	glLinkProgram(this->m_ProgramID);

	int status;

	glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetProgramiv(this->m_ProgramID, GL_INFO_LOG_LENGTH, &status);

		char* error = new char[status + 1];

		glGetShaderInfoLog(this->m_ProgramID, status + 1, &status, error);

		LOG_ERROR(error);
		return false;
	}

	return true;
}

ShaderProgram::~ShaderProgram()
{

}