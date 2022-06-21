#pragma once

#include <map>
#include <vector>
#include <memory>
#include "model.h"

class WorldObj
{
public:
	~WorldObj(); // destructor must free all models
	void render();
	bool model_exists(std::string const name) const;
	void reset_model_color(std::string const name);

protected:
	std::map<std::string, Model *> models; // index 0 is root model, beware that root may have forward_list to children
};

class World
{
public:
	void spawn_object(std::string const name, WorldObj obj);
	void remove_object(std::string const name);
	void render();
	void select();
	void deselect();

private:
	bool worldobj_exists(std::string const name) const;
	bool model_exists(std::string const world_obj_name, std::string const model_name) const;
	std::map<std::string, WorldObj> world_objs;
	std::pair<std::string, std::string> selected; // first = WorldObj, second = Model
};

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};
