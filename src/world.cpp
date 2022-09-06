#include "world.h"
#include "model.h"
#include "main.h"

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
	/// Hardcoded constructor of a skeleton
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
}

void World::spawn_object(std::string const name, WorldObj obj)
{
	this->world_objs.insert({name, obj});
};

void World::remove_object(std::string const name)
{
	this->world_objs.erase(name);
}

void World::render()
{
	for (std::pair<std::string, WorldObj> obj : this->world_objs)
		obj.second.render();
}

std::optional<std::weak_ptr<Model>> World::select_model()
{
	using namespace std;
	// Let go of any previously selected
	this->deselect_model();

	// Get WorldObj
	cin.clear();
	cout << "Please enter the name of the WorldObj you wish to select a Model from:" << endl;
	string world_obj_name;
	cin >> world_obj_name;
	cin.clear();
	map<string, WorldObj>::iterator world_obj = this->world_objs.find(world_obj_name);
	if (world_obj == this->world_objs.end())
	{
		cin.clear();
		PRINT_OUT("Selection failed: WorldObj not found.");
		return this->selected_model;
	}

	// Get Model
	cin.clear();
	cout << "Please enter the name of the Model you wish to select from this WorldObj" << endl;
	string model_name;
	cin >> model_name;
	cin.clear();
	optional<weak_ptr<Model>> model = this->get_model(world_obj->second, model_name);

	// Set new model, if successfully extracted
	if (model)
	{
		this->selected_model = model.value();
		PRINT_OUT("Selection succesful.");
	}
	else
		PRINT_OUT("Selection failed: Model not found.");
	return this->selected_model;
}

void World::select_animation()
{
	using namespace std;

	// Get WorldObj
	cin.clear();
	cout << "Please enter the name of the WorldObj you wish to select a Model from:" << endl;
	string world_obj_name;
	cin >> world_obj_name;
	cin.clear();
	map<string, WorldObj>::iterator world_obj = this->world_objs.find(world_obj_name);
	if (world_obj == this->world_objs.end())
	{
		cin.clear();
		PRINT_OUT("Selection failed: WorldObj not found.");
		return;
	}

	// Get Animation name
	cin.clear();
	cout << "Please enter the name of the Animation you wish to select from this WorldObj" << endl;
	string animation_name;
	cin >> animation_name;
	cin.clear();

	// Set Animation in WorldObj
	try
	{
		world_obj->second.set_animation(animation_name);
	}
	catch (...)
	{
		PRINT_OUT("Error setting animation to WorldObj, most likely WorldObj doesn't have that animation");
	}
}

void World::deselect_model()
{
	this->selected_model.reset();
}

std::shared_ptr<Model> World::get_selected()
{
	return this->selected_model.lock();
}

std::optional<std::weak_ptr<Model>> World::get_model(
	WorldObj &world_obj,
	std::string const &model_name)
{
	auto model = world_obj.models.find(model_name);
	if (model == world_obj.models.end())
		return std::nullopt;
	return std::weak_ptr<Model>(model->second);
}

void World::update(std::chrono::steady_clock::time_point const now)
{
	for (auto world_obj : this->world_objs)
		world_obj.second.update(now);
}

void WorldObj::map_models(std::shared_ptr<Model> model)
{
	this->models.insert({model->get_name(), model});
	for (std::shared_ptr<Model> child : model->children)
		this->map_models(child);
}

void WorldObj::set_animation(std::string const &animation_name)
{
	std::map<std::string, std::shared_ptr<Animation>>::iterator ptr =
		this->animations.find(animation_name);
	if (ptr == this->animations.end())
		throw;
	this->selected_animation = ptr->second;
}

void WorldObj::render()
{
	this->root->render();
}

void WorldObj::update(std::chrono::steady_clock::time_point const now)
{
	if (this->selected_animation.expired())
		return;
	std::shared_ptr<Animation> animation = this->selected_animation.lock();
	nanoseconds current_frame = ((this->last_update_animation_frame + (now - this->last_update_timestamp)) % animation->get_duration());
	std::map<std::string, Frame> const new_frames = animation->get_animated_frames(current_frame);
	for (std::pair<std::string, std::shared_ptr<Model>> model : this->models)
	{
		std::map<std::string, Frame>::const_iterator frame = new_frames.find(model.first);
		if (frame != new_frames.end())
			continue;
		model.second->set_position(frame->second.translations);
	}
}

void WorldObj::unset_animation()
{
	this->selected_animation.reset();
}

Skelly::Skelly(std::shared_ptr<Shader> const shader)
{
	this->root = create_torso(shader);
	this->map_models(this->root);
}
