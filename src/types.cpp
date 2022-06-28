#include "types.h"
#include <cmath>
#include "glm/gtc/quaternion.hpp"

vec3 addition_vec3(vec3 const a, vec3 const b)
{
	return vec3{a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

// dot multiplication of two mat4s
mat4 dot_product_mat4(mat4 const a, mat4 const b)
{
	mat4 out{0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f};

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			for (unsigned int k = 0; k < 4; k++)
			{
				out[i * 4 + j] +=
					a[i * 4 + k] * b[k * 4 + j];
			}
	return out;
}

vec3 normalize_vec3(vec3 const vec)
{
	GLfloat magnitude = sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
	if (magnitude == 0)
		return vec;
	return vec3{vec[0] / magnitude, vec[1] / magnitude, vec[2] / magnitude};
}

mat4 get_scaling_mat4(GLfloat const x, GLfloat const y, GLfloat const z)
{
	return mat4{1.0f + x, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f + y, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f + z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f};
}

vec3 cross_product_vec3(vec3 const a, vec3 const b)
{
	return vec3{a[1] * b[2] - a[2] * b[1],
				a[2] * b[0] - a[0] * b[2],
				a[0] * b[1] - a[1] * b[0]};
}

vec3 subtract_vec3(vec3 const minuend, vec3 const subtrahend)
{
	return vec3{minuend[0] - subtrahend[0],
				minuend[1] - subtrahend[1],
				minuend[2] - subtrahend[2]};
}

mat4 get_translation_mat4(GLfloat const x, GLfloat const y, GLfloat const z)
{
	return mat4{1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f + x, 0.0f + y, 0.0f + z, 1.0f};
}

mat4 get_projection_mat4(
	GLfloat const fov,
	GLfloat const aspect,
	GLfloat const near,
	GLfloat const far)
{
	GLfloat f = (GLfloat)tan(fov / 2.0f);
	return mat4{1.0f / (f * aspect), 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f / f, 0.0f, 0.0f,
				0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
				0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f};
}

/// Quaternion rotation
mat4 get_rotation_mat4(GLfloat const x, GLfloat const y, GLfloat const z)
{
	glm::mat4 mat(glm::quat(glm::vec3(x, y, z))); // Use quaternion to avoid gimbal lock
	return mat4{
		mat[0][0],
		mat[0][1],
		mat[0][2],
		mat[0][3],
		mat[1][0],
		mat[1][1],
		mat[1][2],
		mat[1][3],
		mat[2][0],
		mat[2][1],
		mat[2][2],
		mat[2][3],
		mat[3][0],
		mat[3][1],
		mat[3][2],
		mat[3][3]};
}

mat4 get_lookat_mat4(vec3 const cam_pos, vec3 const target, vec3 const up)
{
	vec3 const f = normalize_vec3(subtract_vec3(target, cam_pos));
	vec3 const s = normalize_vec3(cross_product_vec3(f, up));
	vec3 const u = cross_product_vec3(s, f);

	return mat4{s[0],
				u[0],
				-f[0],
				0.0f,
				s[1],
				u[1],
				-f[1],
				0.0f,
				s[2],
				u[2],
				-f[2],
				0.0f,
				-(s[0] * cam_pos[0] + s[1] * cam_pos[1] + s[2] * cam_pos[2]),
				-(u[0] * cam_pos[0] + u[1] * cam_pos[1] + u[2] * cam_pos[2]),
				-(f[0] * cam_pos[0] + f[1] * cam_pos[1] + f[2] * cam_pos[2]),
				1.0f};
}
