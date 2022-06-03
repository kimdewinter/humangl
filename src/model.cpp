#include "model.h"
#include "main.h"
#include <cmath>

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
}

Model::Model(
	std::string const name,
	std::forward_list<Model *> const children,
	std::vector<std::vector<vec3>> const vertices,
	std::vector<unsigned int> const indices,
	std::shared_ptr<Shader> const shader,
	vec3 const position,
	vec3 const orientation,
	vec3 const scale,
	vec4 const color)
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
	gl_obj(GlObj(vertices, indices))
{
}
catch (char const *const msg)
{
	PRINT_OUT(msg);
}

Model::~Model()
{
	for (Model *child : this->children)
		delete child;
};

void Model::render(mat4 const parent_mat) const
{
	mat4 translation = get_translation_mat4(this->position[0], this->position[1], this->position[2]);
	mat4 scaling = get_scaling_mat4(this->scale[0], this->scale[1], this->scale[2]);
	mat4 rotation = get_rotation_mat4(this->orientation[0], this->orientation[1], this->orientation[2]);
	mat4 final = multiply_mat4(multiply_mat4(multiply_mat4(scaling, rotation), translation), parent_mat);
	this->gl_obj.render(
		this->shader,
		[&]()
		{
			GLuint id = this->shader->get_id();
			set_uniform_mat4(
				id,
				"model",
				final);
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

	for (Model *child : this->children)
	{
		child->render(final);
	}
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
	this->scale = addition_vec3(this->scale, additives);
}

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

Model *Model::find_child(std::string const name)
{
	if (name == this->name)
		return this;
	for (Model *child : this->children)
	{
		if (child->find_child(name))
			return child;
	}
	return nullptr;
}
