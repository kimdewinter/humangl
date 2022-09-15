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
	void render();
	void update(
		std::chrono::steady_clock::time_point const now,
		std::chrono::steady_clock::time_point const last_update);
	std::optional<std::weak_ptr<Model>> select_model();
	void deselect_model();
	std::shared_ptr<Model> get_selected();
	std::optional<std::weak_ptr<Model>> get_model(
		WorldObj &world_obj,
		std::string const &model_name);
	void select_animation();

private:
	std::map<std::string, WorldObj> world_objs;
	std::weak_ptr<Model> selected_model;
};

/// WorldObj is an object in the world, consisting out of one or more Models
class WorldObj
{
public:
	/// @param root the root model with it's children Models attached
	/// @param animations a map of all Animations the WorldObj should be able to perform
	/// @param anim_at_start optional setting of starting animation
	WorldObj(
		std::shared_ptr<Model> root,
		std::map<std::string, std::shared_ptr<Animation>> animations,
		std::string const &anim_at_start = {});
	void render();
	void update(
		std::chrono::steady_clock::time_point const now,
		std::chrono::steady_clock::time_point const last_update);
	void map_models(std::shared_ptr<Model> model);
	friend std::optional<std::weak_ptr<Model>> World::get_model(
		WorldObj &world_obj,
		std::string const &model_name);
	void set_animation(std::string const &animation_name);
	void unset_animation();

protected:
	std::shared_ptr<Model> root;
	std::map<std::string, std::shared_ptr<Model>> models;
	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::weak_ptr<Animation> selected_animation;										// The animation the WorldObj is performaing
	std::chrono::nanoseconds last_update_animation_frame = std::chrono::nanoseconds(0); // Last update ended this far into the animation
};
