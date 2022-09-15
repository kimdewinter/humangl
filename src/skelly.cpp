#include <chrono>
#include "skelly.h"

namespace
{
	/// Use to get the vertices of a 1x1x1 cube
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

	/// Use to get the indices of above 1x1x1 cube
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
}

namespace Skelly
{
	std::shared_ptr<Model> create_right_lower_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_lower_leg",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, -1.2, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.625, 0.2, -0.625},						 // Scale
				{1.0, 1.0, 0.0, 0.0},						 // Color
				{0.0, -0.6, 0.0}}};							 // Joint
	}
	std::shared_ptr<Model> create_right_upper_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_upper_leg", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_right_lower_leg(shader)}, // Children
				get_cube_vertices(),				 // Vertices
				get_cube_indices(),					 // Indices
				shader,								 // Shader
				{-0.25, -1.6, 0.0},					 // Position
				{0.0, 0.0, 0.0},					 // Orientation
				{-0.625, 0.2, -0.625},				 // Scale
				{1.0, 1.0, 0.0, 0.0},				 // Color
				{0.0, -0.6, 0.0}}};					 // Joint
	}
	std::shared_ptr<Model> create_left_lower_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_lower_leg",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, -1.2, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.625, 0.2, -0.625},						 // Scale
				{1.0, 1.0, 0.0, 0.0},						 // Color
				{0.0, -0.6, 0.0}}};							 // Joint
	}
	std::shared_ptr<Model> create_left_upper_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_upper_leg", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_left_lower_leg(shader)}, // Children
				get_cube_vertices(),				// Vertices
				get_cube_indices(),					// Indices
				shader,								// Shader
				{0.25, -1.6, 0.0},					// Position
				{0.0, 0.0, 0.0},					// Orientation
				{-0.625, 0.2, -0.625},				// Scale
				{1.0, 1.0, 0.0, 0.0},				// Color
				{0.0, -0.6, 0.0}}};					// Joint
	}
	std::shared_ptr<Model> create_right_lower_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_lower_arm",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, -1.2, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.7, 0.2, -0.7},							 // Scale
				{1.0, 1.0, 0.0, 0.0},						 // Color
				{0.0, -0.55, 0.0}}};						 // Joint
	}
	std::shared_ptr<Model> create_right_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_upper_arm", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_right_lower_arm(shader)}, // Children
				get_cube_vertices(),				 // Vertices
				get_cube_indices(),					 // Indices
				shader,								 // Shader
				{-0.67, 0.3, 0.0},					 // Position
				{0.0, 0.0, 0.0},					 // Orientation
				{-0.7, 0.2, -0.7},					 // Scale
				{1.0, 1.0, 0.0, 0.0},				 // Color
				{0.0, -0.55, 0.0}}};				 // Joint
	}
	std::shared_ptr<Model> create_left_lower_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_lower_arm",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, -1.2, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.7, 0.2, -0.7},							 // Scale
				{1.0, 1.0, 0.0, 0.0},						 // Color
				{0.0, -0.55, 0.0}}};						 // Joint
	}
	std::shared_ptr<Model> create_left_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_upper_arm", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_left_lower_arm(shader)}, // Children
				get_cube_vertices(),				// Vertices
				get_cube_indices(),					// Indices
				shader,								// Shader
				{0.67, 0.3, 0.0},					// Position
				{0.0, 0.0, 0.0},					// Orientation
				{-0.7, 0.2, -0.7},					// Scale
				{1.0, 1.0, 0.0, 0.0},				// Color
				{0.0, -0.55, 0.0}}};				// Joint
	}
	std::shared_ptr<Model> create_head(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"head",										 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, 1.3, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.4, -0.4, -0.65},						 // Scale
				{1.0, 1.0, 0.0, 0.0},						 // Color
				{0.0, 0.2, 0.0}}};							 // Joint
	}

	std::shared_ptr<Model> create_torso(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"torso", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_head(shader),
					create_left_upper_arm(shader),
					create_right_upper_arm(shader),
					create_left_upper_leg(shader),
					create_right_upper_leg(shader)}, // Children
				get_cube_vertices(),				 // Vertices
				get_cube_indices(),					 // Indices
				shader,								 // Shader
				{0.0, 0.75, -3.0},					 // Position
				{0.0, 0.0, 0.0},					 // Orientation
				{0.0, 1.0, -0.5},					 // Scale
				{1.0, 1.0, 0.0, 0.0}}};				 // Color
	}

	// This function exists because calling "Skelly::create_skelly()" is more intuitive
	// than having to call "Skelly::create_torso()",
	// which might give the illusion that only the torso is returned
	std::shared_ptr<Model> create_skelly(std::shared_ptr<Shader> const shader)
	{
		return create_torso(shader);
	}

	std::pair<std::string, Channel<Keyframe>> walk_head()
	{
		using std::chrono::nanoseconds;
		Keyframe first = {
			{
				.rotations = {0.0, 0.3, 0.0},
			},
			.time = nanoseconds(0),
		};

		return {
			"head",
			Channel<Keyframe>{
				.model_frames = {
					first,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_torso()
	{
		Keyframe first = {
			{
				.translations = {0.0, 0.0, 0.0},
				.rotations = {0.0, -1.0, 0.0},
				.scalings = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.translations = {0.0, 0.0, 0.0},
				.rotations = {0.0, 1.0, 0.0},
				.scalings = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe third = {
			{
				.translations = {0.0, 0.0, 0.0},
				.rotations = {0.0, -1.0, 0.0},
				.scalings = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"torso",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
				},
			},
		};
	}

	/// Hardcoded constructor of a skeleton's animation
	std::shared_ptr<Animation> create_animation_walk()
	{
		return std::shared_ptr<Animation>{
			new Animation{
				std::map<std::string, Channel<Keyframe>>{
					walk_torso(),
				},
			},
		};
	}
}