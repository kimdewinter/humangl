#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * model * vec4(Position, 1.0);
}
