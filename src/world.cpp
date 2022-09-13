#include "world.h"
#include "model.h"
#include "main.h"
#include "animator.h"
#include "skelly.h"

namespace
{
	/// Returns how many nanoseconds into the animation we should currently be
	std::chrono::nanoseconds calculate_current_frame(
		std::chrono::steady_clock::time_point const current_timestamp,
		std::chrono::steady_clock::time_point const last_update_timestamp,
		std::chrono::nanoseconds const last_update_nanoseconds_into_animation,
		std::chrono::nanoseconds const animation_duration)
	{
		// If animation has only one Keyframe, just return 0 nanoseconds,
		// otherwise modulo will cause a floating point error
		if (animation_duration == std::chrono::nanoseconds(0))
			return std::chrono::nanoseconds(0);

		// You take the amount of nanoseconds between last_update_timestamp and current_timestamp,
		// you add how many nanoseconds into the animation it was on the last update,
		// and then modulo in case the result is longer than the nanosecond-duration of the entire animation
		// this tells you how many nanoseconds into the animation we should be in the present

		// Calculate the nanoseconds since last update
		std::chrono::nanoseconds time_since_last_update = current_timestamp - last_update_timestamp;

		// Add this to how far into the animation we were last update,
		// this may be 0,
		// this may also be longer than the length of the entire animation
		std::chrono::nanoseconds intermediary_frame =
			last_update_nanoseconds_into_animation + time_since_last_update;

		// In case of 0, we don't want to modulo but just return 0
		if (intermediary_frame == std::chrono::nanoseconds(0))
			return std::chrono::nanoseconds(0);

		// Otherwise, modulo to loop around the beginning of the animation and return the right frame
		return (intermediary_frame % animation_duration);
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
		PRINT_OUT("Model selection succesful.");
	}
	else
		PRINT_OUT("Model selection failed: Model not found.");
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
	PRINT_OUT("Animation selection succesful.");
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

void World::update(
	std::chrono::steady_clock::time_point const now,
	std::chrono::steady_clock::time_point const last_update)
{
	for (auto iter = this->world_objs.begin(); iter != this->world_objs.end(); iter++)
		iter->second.update(now, last_update);
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
		throw std::runtime_error("Animation not found.");
	this->selected_animation = ptr->second;
}

void WorldObj::render()
{
	this->root->render();
}

void WorldObj::update(
	std::chrono::steady_clock::time_point const now,
	std::chrono::steady_clock::time_point const last_update)
{
	// If current WorldObj isn't doing any kind of animation, we can leave it as-is
	if (this->selected_animation.expired())
		return;

	std::shared_ptr<Animation> animation = this->selected_animation.lock();
	// Find out how many nanoseconds into the animation we should be
	std::chrono::nanoseconds current_frame = calculate_current_frame(
		now,
		last_update,
		this->last_update_animation_frame,
		animation->get_duration());
	this->last_update_animation_frame = current_frame;

	// Now we get the data that tells us how to animate the WorldObj and it's Models, and apply it
	std::map<std::string, Frame> const new_frames = animation->get_animated_frames(current_frame);
	for (std::pair<std::string, std::shared_ptr<Model>> model : this->models)
	{
		std::map<std::string, Frame>::const_iterator frame = new_frames.find(model.first);
		if (frame == new_frames.end())
			continue;
		model.second->reset_position();
		model.second->modify_position(frame->second.translations);
		model.second->reset_orientation();
		model.second->modify_orientation(frame->second.rotations);
		model.second->reset_scale();
		model.second->modify_scale(frame->second.scalings);
	}
}

void WorldObj::unset_animation()
{
	this->selected_animation.reset();
}

Skelly::Skelly(std::shared_ptr<Shader> const shader)
{
	this->root = SkellyCreation::create_torso(shader);
	this->map_models(this->root);
	this->animations.insert({"walk", SkellyAnimation::create_animation_walk()});
#if SET_ANIM_AT_START == 1
	this->set_animation(ANIM_AT_START);
#endif
}
