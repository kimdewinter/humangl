#pragma once

#include <glad/glad.h>
#include <forward_list>
#include <string>
#include <vector>
#include <memory>
#include "types.h"
#include "globj.h"
#include "shader.h"

class Model
{
public:
	Model(
		std::string const name,
		std::forward_list<Model *> const children,
		std::vector<std::vector<vec3>> const vertices,
		std::vector<unsigned int> const indices,
		std::shared_ptr<Shader> const shader,
		vec3 const position,
		vec3 const orientation,
		vec3 const scaling,
		vec4 const color);
	~Model();
	void render() const;

private:
	std::string const name;
	std::forward_list<Model *> const children;

	vec3 position;
	vec3 orientation;
	vec3 scaling;

	vec4 color;

	std::shared_ptr<Shader> const shader;
	GlObj const gl_obj;
};
