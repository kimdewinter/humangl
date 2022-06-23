#pragma once

#include <map>
#include <vector>
#include <memory>
#include "model.h"

class WorldObj
{
public:
	void render();

protected:
	std::map<std::string, std::shared_ptr<Model>> models; // index 0 is root model, beware that root may have forward_list to children
};

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};

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
