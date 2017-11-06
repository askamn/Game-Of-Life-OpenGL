#version 330 core

in vec3 outColor;
out vec4 glFragColor;

void main()
{
	glFragColor = vec4(outColor, 1.0f);//vec4(1.0f, 0.0f, 0.0f, 1.0f);
}