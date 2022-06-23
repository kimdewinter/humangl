#include "world.h"
#include "main.h"

void WorldObj::render()
{
	this->models.begin()->second->render();
	// std::cout << "check world.cpp:50!" << std::endl;
	// this->models[0]->render(); // TO DO: check if this one is necessary instead of line above
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
		return std::make_shared<Model>(
			Model{
				"head",										 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.0, 0.71, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.4, -0.6, -0.4},							 // Scale
				{1.0, 1.0, 0.0, 0.0}});						 // Color
	}

	std::shared_ptr<Model> create_left_upper_arm(std::shared_ptr<Shader> const shader)
	{
		return std::make_shared<Model>(
			Model{
				"left_upper_arm",							 // Name
				std::forward_list<std::shared_ptr<Model>>{}, // Children
				get_cube_vertices(),						 // Vertices
				get_cube_indices(),							 // Indices
				shader,										 // Shader
				{0.67, 0.07, 0.0},							 // Position
				{0.0, 0.0, 0.0},							 // Orientation
				{-0.7, -0.33, -0.7},						 // Scale
				{1.0, 1.0, 0.0, 0.0}});						 // Color
	}

	std::shared_ptr<Model> create_torso(std::shared_ptr<Shader> const shader)
	{
		return std::make_shared<Model>(
			Model{
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
				{1.0, 0.0, 0.0, 0.0}});				// Color
	}
}

Skelly::Skelly(std::shared_ptr<Shader> const shader)
{
	this->models.insert({"torso", create_torso(shader)});
	// this->models = create_torso(shader)->map_all();
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

// void World::deselect()
// {
// 	if (this->selected == std::pair<std::string, std::string>{"", ""})
// 		return;
// 	if (model_exists(this->selected.first, this->selected.second))
// 		this->world_objs.find(this->selected.first)->second.reset_model_color(this->selected.second);
// 	this->selected = {"", ""};
// }

// void World::select()
// {
// 	using namespace std;
// 	if (this->selected == std::pair<std::string, std::string>{"", ""})
// 		this->deselect();
// 	cout << "Please enter the name of an existing object(WorldObj class): ";
// 	string worldobj;
// 	cin >> worldobj;
// 	if (!this->worldobj_exists(worldobj))
// 	{
// 		PRINT_OUT("Not found.");
// 		return;
// 	}

// 	cout << "Please enter the name of an existing part(Model class) of aforementioned object: ";
// 	string model;
// 	cin >> model;
// 	if (!this->model_exists(worldobj, model))
// 	{
// 		PRINT_OUT("Not found.");
// 		return;
// 	}

// 	this->selected = {worldobj, model};
// 	PRINT_OUT("Selection succesful.");
// }
