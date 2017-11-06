#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

uniform mat4 pr_matrix = mat4(1.0f);
uniform vec4 input_position;

out vec3 outColor;

void main()
{
	gl_Position = pr_matrix * (vec4(position.x + input_position.x, position.y + input_position.y, position.zw));
	outColor = color;
}