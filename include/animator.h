#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include "types.h"

struct Frame
{
	vec3 const translations = {0.0, 0.0, 0.0};
	vec3 const rotations = {0.0, 0.0, 0.0};
	vec3 const scalings = {0.0, 0.0, 0.0};
};

struct Keyframe : public Frame
{
	std::chrono::nanoseconds const time = std::chrono::nanoseconds(0); // Time since beginning of animation
};

/// Holds all the keyframes for a Model,
/// T should be a Frame or Keyframe, depending on what Channel is used for
template <typename T>
struct Channel
{
	std::vector<T> const model_frames;
};

/// Data repository for a WorldObj's single animation, only constant members
class Animation
{
public:
	Animation(
		std::map<std::string, Channel<Keyframe>> const &channels);
	std::chrono::nanoseconds const get_duration() const;
	Frame const get_animated_frame(
		std::string const &model_name,
		std::chrono::nanoseconds const time_elapsed) const;
	std::map<std::string, Frame> const get_animated_frames(
		std::chrono::nanoseconds const animation_frame) const;

private:
	std::vector<Keyframe> const &get_channel(std::string const &model_name) const;

	std::chrono::nanoseconds const duration;
	std::map<std::string, Channel<Keyframe>> const channels;
};
