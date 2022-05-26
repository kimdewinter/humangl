#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

/// X, Y, Z
#define SIZE_VEC3 sizeof(GLfloat) * 3
typedef std::array<GLfloat, 3> vec3;

/// X, Y, Z, W
#define SIZE_VEC4 sizeof(GLfloat) * 4
typedef std::array<GLfloat, 4> vec4;

/// Column-first 4x4 float matrix
#define SIZE_MAT4 sizeof(GLfloat) * 16
typedef std::array<GLfloat, 16> mat4;

vec3 addition_vec3(vec3 const a, vec3 const b);
mat4 get_identity_matrix();
mat4 multiply_mat4(mat4 const a, mat4 const b);
vec3 normalize_vec3(vec3 const vec);
mat4 get_scaling_mat4(GLfloat const x, GLfloat const y, GLfloat const z);
vec3 cross_product_vec3(vec3 const a, vec3 const b);
vec3 subtract_vec3(vec3 const minuend, vec3 const subtrahend);
mat4 get_translation_mat4(GLfloat const x, GLfloat const y, GLfloat const z);
mat4 get_projection_mat4(
	GLfloat const fov,
	GLfloat const aspect,
	GLfloat const near,
	GLfloat const far);
mat4 get_orientation_mat4(GLfloat const x, GLfloat const y, GLfloat const z);
mat4 get_lookat_mat4(vec3 const cam_pos, vec3 const target, vec3 const up);
