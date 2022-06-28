#pragma once

#include <map>
#include <vector>
#include <memory>
#include "model.h"

/// WorldObj is an object in the world, consisting out of one or more Models
class WorldObj
{
public:
	void render();

protected:
	std::shared_ptr<Model> root;
	std::map<std::string, std::shared_ptr<Model>> models;
};

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};

/// Contains all the worlds WorldObj instances, as well as the selection controller
class World
{
public:
	void spawn_object(std::string const name, WorldObj obj);
	void remove_object(std::string const name);
	void render();
	// void select();
	// void deselect();

private:
	std::map<std::string, WorldObj> world_objs;
};
