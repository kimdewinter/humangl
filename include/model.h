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
		std::forward_list<Model *> children,
		std::vector<std::vector<vec3>> const vertices,
		std::vector<unsigned int> const indices,
		std::shared_ptr<Shader> const shader,
		vec3 const position,
		vec3 const orientation,
		vec3 const scale,
		vec4 const color);
	~Model();
	std::string get_name() const { return this->name; };
	void render(mat4 const parent_mat = {1.0, 0.0, 0.0, 0.0,
										 0.0, 1.0, 0.0, 0.0,
										 0.0, 0.0, 1.0, 0.0,
										 0.0, 0.0, 0.0, 1.0}) const;
	void modify_position(vec3 const additives);
	void modify_orientation(vec3 const additives);
	void modify_scale(vec3 const additives);
	void reset_position() { this->position = this->default_position; };
	void reset_orientation() { this->orientation = this->default_orientation; };
	void reset_scale() { this->scale = this->default_scale; };
	void debug_model_data() const;
	void set_child(Model *child);
	void set_child(std::vector<Model *> children);
	Model *find_child(std::string const name);
	std::vector<Model *> const get_all_children();

private:
	std::string const name;
	std::forward_list<Model *> children;

	float test = 0.0f;

	vec3 position; // Relative to parent (or world if Model instance is the root part)
	vec3 const default_position;
	vec3 orientation;
	vec3 const default_orientation;
	vec3 scale;
	vec3 const default_scale;

	vec4 color;

	std::shared_ptr<Shader> const shader;
	GlObj const gl_obj;

	void get_all_children_helper(std::vector<Model *> &vec);
};
