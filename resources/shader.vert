#version 410 core

layout (location = 0) in vec3 Position;

uniform mat4 position;
uniform mat4 orientation;
uniform mat4 scaling;
uniform mat4 projection;

mat4 get_identity_matrix()
{
	return mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

void main()
{
	gl_Position = scaling  * position * orientation * vec4(Position, 1.0);
}
