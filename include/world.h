#pragma once

#include <map>
#include <vector>
#include <memory>
#include <optional>
#include <chrono>
#include "shader.h"
#include "animator.h"

class Model;
class WorldObj;

/// Contains all the worlds WorldObj instances, as well as the selection controller
class World
{
public:
	void spawn_object(std::string const name, WorldObj obj);
	void remove_object(std::string const name);
	void render(std::chrono::steady_clock::time_point const now);
	std::optional<std::weak_ptr<Model>> select();
	void deselect();
	std::shared_ptr<Model> get_selected();
	std::optional<std::weak_ptr<Model>> get_model(
		WorldObj &world_obj,
		std::string const &model_name);

private:
	std::map<std::string, WorldObj> world_objs;
	std::weak_ptr<Model> selected;
};

/// WorldObj is an object in the world, consisting out of one or more Models
/// It is not meant to be used directly, instead inherit from it and create a specific constructor
class WorldObj
{
public:
	void render(std::chrono::steady_clock::time_point const now);
	void map_models(std::shared_ptr<Model> model);
	friend std::optional<std::weak_ptr<Model>> World::get_model(
		WorldObj &world_obj,
		std::string const &model_name);

protected:
	std::shared_ptr<Model> root;
	std::map<std::string, std::shared_ptr<Model>> models;
	std::map<std::string, Animation> animations;
};

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};
