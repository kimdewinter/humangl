#include "model.h"
#include <cmath>
#include <functional>

namespace
{
	void set_uniform_vec3(const GLuint shader_id, std::string const uniform_name, vec3 const &value)
	{
		glUniform3f(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			value[0],
			value[1],
			value[2]);
	}

	void set_uniform_vec4(const GLuint shader_id, std::string const uniform_name, vec4 const &value)
	{
		glUniform4f(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			value[0],
			value[1],
			value[2],
			value[3]);
	}

	void set_uniform_mat4(const GLuint shader_id, std::string const uniform_name, mat4 const &value)
	{
		glUniformMatrix4fv(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			1,
			GL_FALSE,
			value.data());
	}

	GLfloat degrees_to_radians(GLfloat const degrees)
	{
		return degrees * (M_PI / 180);
	}

	GLfloat ensure_positive(GLfloat const f)
	{
		return f + static_cast<GLfloat>(1.0);
	}

	mat4 get_rotation_around_joint(
		GLfloat x,
		GLfloat y,
		GLfloat z,
		GLfloat joint_x,
		GLfloat joint_y,
		GLfloat joint_z)
	{
		mat4 pre_translate = get_translation_mat4(joint_x, joint_y, joint_z);
		mat4 rotate = get_rotation_mat4(x, y, z);
		mat4 post_translate = get_translation_mat4(-joint_x, -joint_y, -joint_z);
		return dot_product_mat4(dot_product_mat4(pre_translate, rotate), post_translate);
	}
}

Model::Model(
	std::string const name,
	std::forward_list<std::shared_ptr<Model>> const children,
	std::vector<std::vector<vec3>> const vertices,
	std::vector<unsigned int> const indices,
	std::shared_ptr<Shader> const shader,
	vec3 const position,
	vec3 const orientation,
	vec3 const scale,
	vec4 const color,
	vec3 const joint,
	std::array<bool, ELEMENTS_VEC3> const allow_scaling)
try : name(name),
	children(children),
	shader(shader),
	position(position),
	default_position(position),
	orientation(orientation),
	default_orientation(orientation),
	scale(scale),
	default_scale(scale),
	color(color),
	default_color(color),
	joint(joint),
	allow_scaling(allow_scaling),
	gl_obj(GlObj(vertices, indices))
{
}
catch (char const *const msg)
{
	PRINT_OUT(msg);
}

std::string const Model::get_name() const
{
	return this->name;
}

/// Calcutes transformations, sets uniforms, renders, and calls itself in this->children
void Model::render(
	vec3 const parent_scale,
	vec3 const parent_default_scale,
	mat4 const parent_mat) const
{
	vec3 adjusted_position = {this->position[0], this->position[1], this->position[2]};
#if MODEL_DESIGN_MODE == 0
	{
		for (int i = 0; i < ELEMENTS_VEC3; i++)
		{
			// adjusted_position[i] = this->default_position[i] + ((parent_scale[i] - parent_default_scale[i]) * -this->joint[i]);
			GLfloat scale_combined = ensure_positive(parent_default_scale[i]) + ensure_positive(this->default_scale[i]);
			GLfloat parent_portion = ensure_positive(parent_default_scale[i]) / scale_combined;
			GLfloat child_portion = ensure_positive(this->default_scale[i]) / scale_combined;
			// adjusted_position[i] =
			// 	(this->default_position[i] * parent_portion *
			// 	 ensure_positive(parent_scale[i]) / ensure_positive(parent_default_scale[i])) +
			// 	(this->default_position[i] * child_portion *
			// 	 ensure_positive(this->scale[i]) / ensure_positive(this->default_scale[i])) +
			// 	((parent_scale[i] - parent_default_scale[i]) * -this->joint[i]);
			adjusted_position[i] =
				(this->default_position[i] * parent_portion *
				 ensure_positive(parent_scale[i]) / ensure_positive(parent_default_scale[i])) +
				(this->default_position[i] * child_portion *
				 ensure_positive(this->scale[i]) / ensure_positive(this->default_scale[i])) +
				((ensure_positive(parent_scale[i]) - ensure_positive(parent_default_scale[i])) * -this->joint[i] * parent_portion) +
				((ensure_positive(this->scale[i]) - ensure_positive(this->default_scale[i])) * -this->joint[i] * child_portion);
		}
	}
#endif
	mat4 for_renderer;
	mat4 for_child; // The child models must not receive the scaling aspect of the parent transformation
	{
		mat4 scaling = get_scaling_mat4(this->scale[0], this->scale[1], this->scale[2]);
		mat4 rotation = get_rotation_around_joint(
			this->orientation[0],
			this->orientation[1],
			this->orientation[2],
			this->joint[0],
			this->joint[1],
			this->joint[2]);
		mat4 translation = get_translation_mat4(adjusted_position[0], adjusted_position[1], adjusted_position[2]);
		for_renderer = dot_product_mat4(
			dot_product_mat4(dot_product_mat4(scaling, rotation), translation), parent_mat);
	}
	{
		mat4 rotation = get_rotation_around_joint(
			this->orientation[0],
			this->orientation[1],
			this->orientation[2],
			this->joint[0],
			this->joint[1],
			this->joint[2]);
		mat4 translation = get_translation_mat4(adjusted_position[0], adjusted_position[1], adjusted_position[2]);
		for_child = dot_product_mat4(dot_product_mat4(rotation, translation), parent_mat);
	}
	this->gl_obj.render(
		this->shader,
		[&]()
		{
			GLuint id = this->shader->get_id();
			set_uniform_mat4(
				id,
				"model",
				for_renderer);
			set_uniform_mat4(
				id,
				"projection",
				get_projection_mat4(
					degrees_to_radians(FIELD_OF_VIEW),
					WINDOW_WIDTH / WINDOW_HEIGHT,
					PROJECTION_NEAR,
					PROJECTION_FAR));
			set_uniform_vec4(id, "color_in", this->color);
		});

	for (std::shared_ptr<Model> child : this->children)
		child->render(this->scale, this->default_scale, for_child);
}

void Model::modify_position(vec3 const additives)
{
	this->position = addition_vec3(this->position, additives);
}

void Model::modify_orientation(vec3 const additives)
{
	this->orientation = addition_vec3(this->orientation, additives);
}

void Model::modify_scale(vec3 const additives)
{
	for (int i = 0; i < ELEMENTS_VEC3; i++)
		if (this->allow_scaling[i] || MODEL_DESIGN_MODE)
			this->scale[i] += additives[i];
}

void Model::set_position(vec3 const position)
{
	this->position = position;
}

void Model::set_orientation(vec3 const orientation)
{
	this->orientation = orientation;
}

void Model::set_scale(vec3 const scale)
{
	this->scale = scale;
}

void Model::set_color(vec4 const color)
{
	this->color = color;
}

void Model::reset_position()
{
	this->position = this->default_position;
};

void Model::reset_orientation()
{
	this->orientation = this->default_orientation;
};

void Model::reset_scale()
{
	this->scale = this->default_scale;
};

void Model::reset_color()
{
	this->color = this->default_color;
};

void Model::debug_model_data() const
{
	std::function<void(std::string const, vec3 const &)> print_vec3 = [](std::string const pre_str, vec3 const &vec)
	{
		std::cout << pre_str << vec[0] << ", " << vec[1] << ", " << vec[2] << std::endl;
	};
	std::cout << std::endl
			  << "Printing data of model \"" << this->name << "\"" << std::endl;
	print_vec3("Position: ", this->position);
	print_vec3("Orientation: ", this->orientation);
	print_vec3("Scale: ", this->scale);
	std::cout << std::endl;
}
