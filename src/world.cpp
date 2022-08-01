#include "world.h"
#include "model.h"
#include "main.h"

void WorldObj::render()
{
	this->root->render();
}

void WorldObj::map_models(std::shared_ptr<Model> model)
{
	this->models.insert({model->get_name(), model});
	for (std::shared_ptr<Model> child : model->children)
		this->map_models(child);
}

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

	std::shared_ptr<Model> create_head(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"head",										 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, 0.71, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.4, -0.6, -0.4},							 // Scale
				{1.0, 1.0, 0.0, 0.0}}};						 // Color
	}
	std::shared_ptr<Model> create_left_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"left_upper_arm",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.67, 0.07, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.7, -0.33, -0.7},						 // Scale
				{1.0, 1.0, 0.0, 0.0}}};						 // Color
	}
	std::shared_ptr<Model> create_torso(std::shared_ptr<Shader> const shader)
	{
		return std::shared_ptr<Model>{
			new Model{
				"torso", // Name
				std::forward_list<std::shared_ptr<Model>>{
					create_head(shader),
					create_left_upper_arm(shader)}, // Children
				get_cube_vertices(),				// Vertices
				get_cube_indices(),					// Indices
				shader,								// Shader
				{0.0, 0.75, -3.0},					// Position
				{0.0, 0.0, 0.0},					// Orientation
				{0.0, 1.0, 0.0},					// Scale
				{1.0, 1.0, 0.0, 0.0}}};				// Color
	}
}

Skelly::Skelly(std::shared_ptr<Shader> const shader)
{
	this->root = create_torso(shader);
	this->map_models(this->root);
}

//-----------------------------WORLD--------------------------------------------

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
	{
		obj.second.render();
	}
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

std::optional<std::weak_ptr<Model>> World::select()
{
	using namespace std;
	// Let go of any previously selected
	this->deselect();

	// Get WorldObj
	cout << "Please enter the name of the WorldObj you wish to select a Model from:" << endl;
	string world_obj_name;
	cin >> world_obj_name;
	map<string, WorldObj>::iterator world_obj = this->world_objs.find(world_obj_name);
	if (world_obj == this->world_objs.end())
	{
		cin.clear();
		return nullopt;
	}

	// Get Model
	cout << "Please enter the name of the Model you wish to select from this WorldObj" << endl;
	string model_name;
	cin >> model_name;
	optional<weak_ptr<Model>> model = this->get_model(world_obj->second, model_name);

	// Set new model, if successfully extracted
	if (model)
		this->selected = model.value();
	cin.clear();
	return this->selected;
}
