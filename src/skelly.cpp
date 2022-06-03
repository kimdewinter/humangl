#include "model.h"
#include "skelly.h"

namespace
{
	std::vector<std::vector<vec3>> get_cube_vertices()
	{
		return std::vector<std::vector<vec3>>(
			{
				{
					{-0.5, 0.5, 0.5},
					{-0.5, -0.5, 0.5},
					{0.5, -0.5, 0.5},
					{0.5, 0.5, 0.5},
					{-0.5, 0.5, -0.5},
					{-0.5, -0.5, -0.5},
					{0.5, -0.5, -0.5},
					{0.5, 0.5, -0.5},
				},
			});
	}

	std::vector<unsigned int> get_cube_indices()
	{
		return std::vector<unsigned int>(
			{0, 1, 3,
			 1, 2, 3,
			 7, 6, 4,
			 6, 5, 4,
			 3, 2, 7,
			 2, 6, 7,
			 4, 0, 7,
			 0, 3, 7,
			 4, 5, 0,
			 5, 1, 0,
			 1, 5, 2,
			 5, 6, 2});
	}

	Model *create_torso(std::shared_ptr<Shader> const shader)
	{
		return new Model{
			"torso",					  // Name
			std::forward_list<Model *>(), // Children
			get_cube_vertices(),		  // Vertices
			get_cube_indices(),			  // Indices
			shader,						  // Shader
			{0.0, 0.75, -3.0},			  // Position
			{0.0, 0.0, 0.0},			  // Orientation
			{0.0, 1.0, 0.0},			  // Scale
			{1.0, 0.0, 0.0, 0.0}};		  // Color
	}

	Model *create_head(std::shared_ptr<Shader> const shader)
	{
		return new Model{
			"head",						  // Name
			std::forward_list<Model *>(), // Children
			get_cube_vertices(),		  // Vertices
			get_cube_indices(),			  // Indices
			shader,						  // Shader
			{0.0, 0.71, 0.0},			  // Position
			{0.0, 0.0, 0.0},			  // Orientation
			{-0.4, -0.6, -0.4},			  // Scale
			{1.0, 1.0, 0.0, 0.0}};		  // Color
	}

	Model *create_left_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return new Model{
			"left_upper_arm",			  // Name
			std::forward_list<Model *>(), // Children
			get_cube_vertices(),		  // Vertices
			get_cube_indices(),			  // Indices
			shader,						  // Shader
			{0.67, 0.07, 0.0},			  // Position
			{0.0, 0.0, 0.0},			  // Orientation
			{-0.7, -0.33, -0.7},		  // Scale
			{1.0, 1.0, 0.0, 0.0}};		  // Color
	}
}

namespace Skelly
{
	Model *create_skelly(std::shared_ptr<Shader> const shader)
	{
		Model *torso = create_torso(shader);
		Model *head = create_head(shader);
		Model *left_upper_arm = create_left_upper_arm(shader);
		torso->set_child(head);
		torso->set_child(left_upper_arm);
		return torso;
	}
}
