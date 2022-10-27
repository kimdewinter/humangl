#pragma once

#include <glad/glad.h>
#include <forward_list>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "main.h"
#include "types.h"
#include "globj.h"
#include "shader.h"
#include "world.h"

/// A model is a mesh that can either exist on it's own or be part of a larger collection
/// for instance it can be the left upper arm of a humanoid figure.
/// Model contains a forward_list called "children".
/// A humanoid figure would start with a root Model, and then branch out by attaching child Models
/// whose position and orientation would follow their parent Model.
class Model
{
public:
	/// @param name
	/// @param children Models that should be attached to and below this Model in the matrix hierarchy
	/// @param vertices
	/// @param indices what triangles to draw between the vertices
	/// @param shader shader program to call for rendering
	/// @param position xyz position relative to parent (or world if this is the root model)
	/// @param orientation as above
	/// @param scale as above
	/// @param color
	/// @param joint optional point around which the Model should rotate
	/// @param allow_scaling
	/// @param adjust_for_parent whether, when the parent's scale changes in a certain dimension, this model should shift it's position to still be positioned correctly relative to the parent
	Model(
		std::string const name,
		std::forward_list<std::shared_ptr<Model>> children,
		std::vector<std::vector<vec3>> const vertices,
		std::vector<unsigned int> const indices,
		std::shared_ptr<Shader> const shader,
		vec3 const position,
		vec3 const orientation,
		vec3 const scale,
		vec4 const color,
		vec3 const joint = {0.0, 0.0, 0.0},
		std::array<bool, ELEMENTS_VEC3> const allow_scaling = {},
		vec3 const scaling_offset = {0.0, 0.0, 0.0});
	std::string const get_name() const;
	/// @param parent_mat parent's transformation matrix without scaling (otherwise child scale also changes)
	void render(vec3 const parent_scale = {0.0, 0.0, 0.0},
				vec3 const parent_def_scale = {0.0, 0.0, 0.0},
				mat4 const parent_mat = {1.0, 0.0, 0.0, 0.0,
										 0.0, 1.0, 0.0, 0.0,
										 0.0, 0.0, 1.0, 0.0,
										 0.0, 0.0, 0.0, 1.0}) const;
	void modify_position(vec3 const additives);
	void modify_orientation(vec3 const additives);
	void modify_scale(vec3 const additives);
	void set_position(vec3 const position);
	void set_orientation(vec3 const orientation);
	void set_scale(vec3 const scale);
	void set_color(vec4 const color);
	void reset_position();
	void reset_orientation();
	void reset_scale();
	void reset_color();
	friend void WorldObj::map_models(std::shared_ptr<Model> model);
	void debug_model_data() const;

private:
	std::string const name;
	std::forward_list<std::shared_ptr<Model>> children;
	vec3 position;				 // Relative to parent (or world if Model instance is the root part)
	vec3 const default_position; // Used for resetting
	vec3 orientation;
	vec3 const default_orientation;
	vec3 scale;
	vec3 const default_scale;
	vec4 color;
	vec4 const default_color;
	vec3 const joint;
	std::array<bool, ELEMENTS_VEC3> const allow_scaling;
	vec3 const scaling_offset;
	std::shared_ptr<Shader> const shader;
	GlObj const gl_obj;
};
