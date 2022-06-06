#pragma once

#include <map>
#include <vector>
#include <memory>
#include "model.h"

class Skelly : public WorldObj
{
public:
	Skelly(std::shared_ptr<Shader> const shader);
};

class WorldObj
{
public:
	WorldObj(Model *root);
	~WorldObj();

protected:
	std::map<std::string, Model *> models; // index 0 is the root model
};

class World
{
private:
	std::map<std::string, WorldObj> world_objs;
};
