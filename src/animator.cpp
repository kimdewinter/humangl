#include "animator.h"

namespace
{
	std::chrono::nanoseconds const find_longest_duration(
		std::map<std::string, Channel<Keyframe>> const &channels)
	{
		std::chrono::nanoseconds longest = std::chrono::nanoseconds(0);
		for (std::pair<std::string, Channel<Keyframe>> const channel : channels)
			for (Keyframe const keyframe : channel.second.model_frames)
				if (keyframe.time > longest)
					longest = keyframe.time;
		return longest;
	}

	vec3 const interpolate_vec3(vec3 const &last, vec3 const &next, float const scale_factor)
	{
		return vec3{last[0] + ((next[0] - last[0]) * scale_factor),
					last[1] + ((next[1] - last[1]) * scale_factor),
					last[2] + ((next[2] - last[2]) * scale_factor)};
	}

	Frame const interpolate_frames(
		Keyframe const &last_key,
		Keyframe const &next_key,
		std::chrono::nanoseconds const animation_frame)
	{
		std::chrono::nanoseconds const partway_length = animation_frame - last_key.time;
		std::chrono::nanoseconds const frames_difference = next_key.time - last_key.time;
		double scale_factor = (double)partway_length.count() / (double)frames_difference.count();

		return Frame{
			.translations = interpolate_vec3(
				last_key.translations,
				next_key.translations,
				scale_factor),
			.rotations = interpolate_vec3(last_key.rotations, next_key.rotations, scale_factor),
			.scalings = interpolate_vec3(last_key.scalings, next_key.scalings, scale_factor)};
	}
}

/// Each Channel<Keyframe> simply contains all the keyframes for a given Model,
/// and you must supply a Channel<Keyframe> for every Model that is part of a WorldObj
Animation::Animation(
	std::map<std::string, Channel<Keyframe>> const &channels)
	: duration{find_longest_duration(channels)},
	  channels{channels}
{
}

std::vector<Keyframe> const &Animation::get_channel(std::string const &model_name) const
{
	std::map<std::string, Channel<Keyframe>>::const_iterator channel =
		this->channels.find(model_name);
	if (channel == this->channels.end())
		throw("Could not find requested Channel in Animation.");
	if (channel->second.model_frames.size() < 1)
		throw("Requested Channel had no Keyframes.");
	return channel->second.model_frames;
}

std::chrono::nanoseconds const Animation::get_duration() const
{
	return this->duration;
}

Frame const Animation::get_animated_frame(
	std::string const &model_name,
	std::chrono::nanoseconds const animation_frame) const
{
	std::vector<Keyframe> const &channel = this->get_channel(model_name);

	// If channel consists of 1 frame, there's no next frame to be found
	if (channel.size() == 1)
		return Frame{*channel.begin()};

	// Keep advancing until you find the current time point (between two keyframes)
	std::vector<Keyframe>::const_iterator last_key = channel.begin();
	std::vector<Keyframe>::const_iterator next_key = channel.begin();
	next_key++;
	while (!(last_key->time <= animation_frame && next_key->time >= animation_frame))
	{
		last_key++;
		next_key++;
	}

	// If current time is right on a keyframe, there's no point in interpolating
	if (last_key->time == animation_frame)
		return Frame{*last_key};
	if (next_key->time == animation_frame)
		return Frame{*next_key};
	return interpolate_frames(*last_key, *next_key, animation_frame);
}

/// The data returns can be added to the position, rotation and scaling of a WorldObj's Models
std::map<std::string, Frame> const Animation::get_animated_frames(
	std::chrono::nanoseconds const animation_frame) const
{
	std::map<std::string, Frame> map;
	for (std::pair<std::string, Channel<Keyframe>> channel : this->channels)
		map.insert(std::pair<std::string, Frame>{
			channel.first,
			get_animated_frame(channel.first, animation_frame)});
	return map;
}
