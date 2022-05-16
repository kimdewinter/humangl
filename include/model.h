#pragma once

#include <glad/glad.h>
#include <forward_list>
#include <string>
#include <vector>
#include "types.h"
#include "globj.h"
#include "shader.h"

class Model
{
public:
	Model(
		std::string const name,
		std::forward_list<Model const *> const children,
		std::vector<std::vector<vec3>> const vertices,
		std::vector<unsigned int> const indices,
		std::shared_ptr<Shader> const shader,
		vec3 const position,
		vec3 const orientation,
		vec3 const scaling,
		vec3 const color);
	~Model();
	void render(); // TO IMPLEMENT

private:
	std::string const name;
	std::forward_list<Model const *> const children;

	vec3 position;
	vec3 orientation;
	vec3 scaling;

	vec3 color;

	std::shared_ptr<Shader> const shader;
	GlObj const gl_obj;
};
