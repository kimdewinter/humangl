#pragma once

#include <map>
#include <vector>
#include <memory>
#include <optional>
#include "shader.h"

class Model;
class WorldObj;

/// Contains all the worlds WorldObj instances, as well as the selection controller
class World
{
public:
	void spawn_object(std::string const name, WorldObj obj);
	void remove_object(std::string const name);
	void render();
	std::optional<std::weak_ptr<Model>> select();
	std::shared_ptr<Model> get_selected() { return this->selected.lock(); };
	void deselect() { this->selected.reset(); };
	std::optional<std::weak_ptr<Model>> get_model(WorldObj &world_obj, std::string const &model_name);

private:
	std::map<std::string, WorldObj> world_objs;
	std::weak_ptr<Model> selected;
};

/// WorldObj is an object in the world, consisting out of one or more Models
/// It is not meant to be used directly, instead inherit from it and create a specific constructor
class WorldObj
{
public:
	void render();
	void map_models(std::shared_ptr<Model> model);
	friend std::optional<std::weak_ptr<Model>> World::get_model(
		WorldObj &world_obj,
		std::string const &model_name);

protected:
	std::shared_ptr<Model> root;
	std::map<std::string, std::shared_ptr<Model>> models;
};

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};
