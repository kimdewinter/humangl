#version 410 core

layout (location = 0) in vec3 Position;

uniform mat4 position;
uniform mat4 orientation;
uniform mat4 scaling;
uniform mat4 projection;

void main()
{
	gl_Position = scaling  * position * orientation * vec4(Position, 1.0);
}
