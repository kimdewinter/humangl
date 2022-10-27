#include <chrono>
#include "skelly.h"

#define COLOR_SHIRT_R 0.0f
#define COLOR_SHIRT_G 0.5f
#define COLOR_SHIRT_B 0.0f
#define COLOR_SHIRT_A 1.0f

#define COLOR_PANTS_R 0.2f
#define COLOR_PANTS_G 0.3f
#define COLOR_PANTS_B 0.4f
#define COLOR_PANTS_A 0.0f

#define COLOR_SKIN_R 0.6f
#define COLOR_SKIN_G 0.5f
#define COLOR_SKIN_B 0.4f
#define COLOR_SKIN_A 0.0f

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
	/********************************* MODELS *********************************/

	std::shared_ptr<Model> create_right_lower_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_lower_leg",											  // Name
				std::forward_list<std::shared_ptr<Model>>{},				  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{0.0, -1.2, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.625, 0.2, -0.625},										  // Scale
				{COLOR_PANTS_R, COLOR_PANTS_G, COLOR_PANTS_B, COLOR_PANTS_A}, // Color
				{0.0, -0.6, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{0.0, 0.0, 0.0}}};											  // Scaling Offset
	}
	std::shared_ptr<Model> create_right_upper_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_upper_leg", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_right_lower_leg(shader)},						  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{-0.25, -1.6, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.625, 0.2, -0.625},										  // Scale
				{COLOR_PANTS_R, COLOR_PANTS_G, COLOR_PANTS_B, COLOR_PANTS_A}, // Color
				{0.0, -0.6, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{-0.4, 0.0, 0.0}}};											  // Scaling Offset
	}
	std::shared_ptr<Model> create_left_lower_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_lower_leg",											  // Name
				std::forward_list<std::shared_ptr<Model>>{},				  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{0.0, -1.2, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.625, 0.2, -0.625},										  // Scale
				{COLOR_PANTS_R, COLOR_PANTS_G, COLOR_PANTS_B, COLOR_PANTS_A}, // Color
				{0.0, -0.6, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{0.0, 0.0, 0.0}}};											  // Scaling Offset
	}
	std::shared_ptr<Model> create_left_upper_leg(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_upper_leg", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_left_lower_leg(shader)},							  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{0.25, -1.6, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.625, 0.2, -0.625},										  // Scale
				{COLOR_PANTS_R, COLOR_PANTS_G, COLOR_PANTS_B, COLOR_PANTS_A}, // Color
				{0.0, -0.6, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{-0.4, 0.0, 0.0}}};											  // Scaling Offset
	}
	std::shared_ptr<Model> create_right_lower_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_lower_arm",										  // Name
				std::forward_list<std::shared_ptr<Model>>{},			  // Children
				get_cube_vertices(),									  // Vertices
				get_cube_indices(),										  // Indices
				shader,													  // Shader
				{0.0, -1.2, 0.0},										  // Position
				{0.0, 0.0, 0.0},										  // Orientation
				{-0.7, 0.2, -0.7},										  // Scale
				{COLOR_SKIN_R, COLOR_SKIN_G, COLOR_SKIN_B, COLOR_SKIN_A}, // Color
				{0.0, -0.55, 0.0},										  // Joint
				{false, true, false},									  // Allow Scaling
				{0.0, 0.0, 0.0}}};										  // Scaling Offset
	}
	std::shared_ptr<Model> create_right_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"right_upper_arm", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_right_lower_arm(shader)},						  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{-0.65, 0.3, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.7, 0.2, -0.7},											  // Scale
				{COLOR_SHIRT_R, COLOR_SHIRT_G, COLOR_SHIRT_B, COLOR_SHIRT_A}, // Color
				{0.0, -0.55, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{0.0, -0.55, 0.0}}};										  // Scaling Offset
	}
	std::shared_ptr<Model> create_left_lower_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_lower_arm",										  // Name
				std::forward_list<std::shared_ptr<Model>>{},			  // Children
				get_cube_vertices(),									  // Vertices
				get_cube_indices(),										  // Indices
				shader,													  // Shader
				{0.0, -1.2, 0.0},										  // Position
				{0.0, 0.0, 0.0},										  // Orientation
				{-0.7, 0.2, -0.7},										  // Scale
				{COLOR_SKIN_R, COLOR_SKIN_G, COLOR_SKIN_B, COLOR_SKIN_A}, // Color
				{0.0, -0.55, 0.0},										  // Joint
				{false, true, false},									  // Allow Scaling
				{0.0, 0.0, 0.0}}};										  // Scaling Offset
	}
	std::shared_ptr<Model> create_left_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_upper_arm", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_left_lower_arm(shader)},							  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{0.65, 0.3, 0.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{-0.7, 0.2, -0.7},											  // Scale
				{COLOR_SHIRT_R, COLOR_SHIRT_G, COLOR_SHIRT_B, COLOR_SHIRT_A}, // Color
				{0.0, -0.55, 0.0},											  // Joint
				{false, true, false},										  // Allow Scaling
				{0.0, -0.55, 0.0}}};										  // Scaling Offset
	}
	std::shared_ptr<Model> create_head(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"head",													  // Name
				std::forward_list<std::shared_ptr<Model>>{},			  // Children
				get_cube_vertices(),									  // Vertices
				get_cube_indices(),										  // Indices
				shader,													  // Shader
				{0.0, 1.3, 0.0},										  // Position
				{0.0, 0.0, 0.0},										  // Orientation
				{-0.4, -0.4, -0.65},									  // Scale
				{COLOR_SKIN_R, COLOR_SKIN_G, COLOR_SKIN_B, COLOR_SKIN_A}, // Color
				{0.0, 0.2, 0.0},										  // Joint
				{true, true, true},										  // Allow Scaling
				{0.0, 0.0, 0.0}}};										  // Scaling Offset
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
					create_right_upper_leg(shader)},						  // Children
				get_cube_vertices(),										  // Vertices
				get_cube_indices(),											  // Indices
				shader,														  // Shader
				{0.0, 0.75, -3.0},											  // Position
				{0.0, 0.0, 0.0},											  // Orientation
				{0.0, 1.0, -0.5},											  // Scale
				{COLOR_SHIRT_R, COLOR_SHIRT_G, COLOR_SHIRT_B, COLOR_SHIRT_A}, // Color
				{0.0, 0.0, 0.0},											  // Joint
				{true, true, false},										  // Allow Scaling
				{0.0, 0.0, 0.0}}};											  // Scaling Offset
	}

	// This function exists because calling "Skelly::create_skelly()" is more intuitive
	// than having to call "Skelly::create_torso()",
	// which might give the illusion that only the torso is returned
	std::shared_ptr<Model> create_skelly(std::shared_ptr<Shader> const shader)
	{
		return create_torso(shader);
	}

	/********************************* WALKING ANIMATION *********************************/

	std::pair<std::string, Channel<Keyframe>> walk_left_upper_arm()
	{
		Keyframe first = {
			{
				.rotations = {-0.15, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe third = {
			{
				.rotations = {0.05, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {-0.15, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_upper_arm",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_right_upper_arm()
	{
		Keyframe first = {
			{
				.rotations = {0.05, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(250)),
		};

		Keyframe third = {
			{
				.rotations = {-0.15, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1750)),
		};

		Keyframe fifth = {
			{
				.rotations = {0.05, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_upper_arm",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_left_lower_leg()
	{
		Keyframe first = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe fifth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_lower_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_left_upper_leg()
	{
		Keyframe first = {
			{
				.rotations = {0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500)),
		};

		Keyframe third = {
			{
				.rotations = {-0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe fifth = {
			{
				.rotations = {0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_upper_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_right_lower_leg()
	{
		Keyframe first = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe fifth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_lower_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> walk_right_upper_leg()
	{
		Keyframe first = {
			{
				.rotations = {-0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500)),
		};

		Keyframe third = {
			{
				.rotations = {0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1000)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe fifth = {
			{
				.rotations = {-0.3, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_upper_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
				},
			},
		};
	}

	std::shared_ptr<Animation> create_animation_walk()
	{
		return std::shared_ptr<Animation>{
			new Animation{
				std::map<std::string, Channel<Keyframe>>{
					walk_right_upper_leg(),
					walk_right_lower_leg(),
					walk_left_upper_leg(),
					walk_left_lower_leg(),
					walk_right_upper_arm(),
					walk_left_upper_arm(),
				},
			},
		};
	}

	/********************************* JUMPING ANIMATION *********************************/

	std::pair<std::string, Channel<Keyframe>> jump_left_lower_arm()
	{
		Keyframe first = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_lower_arm",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_right_lower_arm()
	{
		Keyframe first = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {-1.5, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_lower_arm",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_left_lower_leg()
	{
		Keyframe first = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_lower_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_left_upper_leg()
	{
		Keyframe first = {
			{
				.rotations = {-2.0, 0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {-2.0, 0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {-2.0, 0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"left_upper_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_right_lower_leg()
	{
		Keyframe first = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {2.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_lower_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_right_upper_leg()
	{
		Keyframe first = {
			{
				.rotations = {-2.0, -0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.rotations = {0.0, 0.0, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.rotations = {-2.0, -0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.rotations = {-2.0, -0.37, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(2000)),
		};

		return {
			"right_upper_leg",
			Channel<Keyframe>{
				.model_frames = {
					first,
					second,
					third,
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::pair<std::string, Channel<Keyframe>> jump_torso()
	{
		float const rotation = 0.0; // not a proper camera implementation, just a dirty quick-fix

		Keyframe first = {
			{
				.translations = {0.0, -0.78, 0.0},
				.rotations = {0.5, rotation, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(0)),
		};

		Keyframe second = {
			{
				.translations = {0.0, 0.0, 0.0},
				.rotations = {0.0, rotation, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(150)),
		};

		Keyframe third = {
			{
				.translations = {0.0, 0.5, 0.0},
				.rotations = {0.0, rotation, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(750)),
		};

		Keyframe fourth = {
			{
				.translations = {0.0, 0.0, 0.0},
				.rotations = {0.0, rotation, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1250)),
		};

		Keyframe fifth = {
			{
				.translations = {0.0, -0.78, 0.0},
				.rotations = {0.5, rotation, 0.0},
			},
			.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(1500)),
		};

		Keyframe sixth = {
			{
				.translations = {0.0, -0.78, 0.0},
				.rotations = {0.5, rotation, 0.0},
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
					fourth,
					fifth,
					sixth,
				},
			},
		};
	}

	std::shared_ptr<Animation> create_animation_jump()
	{
		return std::shared_ptr<Animation>{
			new Animation{
				std::map<std::string, Channel<Keyframe>>{
					jump_torso(),
					jump_right_upper_leg(),
					jump_right_lower_leg(),
					jump_left_upper_leg(),
					jump_left_lower_leg(),
					jump_right_lower_arm(),
					jump_left_lower_arm(),
				},
			},
		};
	}
}
