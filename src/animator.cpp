#include "animator.h"

namespace
{
    nanoseconds const find_longest_duration(std::vector<Channel<Keyframe>> const &channels)
    {
        nanoseconds longest = nanoseconds(0);
        for (Channel<Keyframe> const channel : channels)
            for (Keyframe const keyframe : channel.model_frames)
                if (keyframe.time > longest)
                    longest = keyframe.time;
        return longest;
    }

    std::map<std::string, Channel<Keyframe>> const
    map_channels(std::vector<Channel<Keyframe>> const &channels)
    {
        std::map<std::string, Channel<Keyframe>> map;
        for (Channel<Keyframe> channel : channels)
            map.emplace(channel.model_name, channel);
        return map;
    }

    vec3 const interpolate_vec3(vec3 const last, vec3 next, float const scale_factor)
    {
        return vec3{last[0] + ((next[0] - last[0]) * scale_factor),
                    last[1] + ((next[1] - last[1]) * scale_factor),
                    last[2] + ((next[2] - last[2]) * scale_factor)};
    }

    Frame const interpolate_frames(
        Keyframe const &last_key,
        Keyframe const &next_key,
        nanoseconds const time_elapsed)
    {
        nanoseconds const mid_way_length = time_elapsed - last_key.time;
        nanoseconds const frames_difference = next_key.time - last_key.time;
        float const scale_factor = mid_way_length / frames_difference;

        return Frame{
            .translations{interpolate_vec3(last_key.translations, next_key.translations, scale_factor)},
            .rotations{interpolate_vec3(last_key.rotations, next_key.rotations, scale_factor)},
            .scalings{interpolate_vec3(last_key.scalings, next_key.scalings, scale_factor)}};
    }
}

/// Each Channel<Keyframe> simply contains all the keyframes for a given Model,
/// and you must supply a Channel<Keyframe> for every Model that is part of a WorldObj
Animation::Animation(
    std::string const animation_name,
    std::vector<Channel<Keyframe>> const &channels)
    : animation_name{animation_name},
      duration{find_longest_duration(channels)},
      channels{map_channels(channels)}
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
    if (channel->second.model_name != model_name)
        throw("Parameter model_name different than member variable model_name in Channel.");
    return channel->second.model_frames;
}

Frame const Animation::get_animated_frame(
    std::string const &model_name,
    nanoseconds const time_elapsed) const
{
    std::vector<Keyframe> const &channel = this->get_channel(model_name);

    // If channel consists of 1 frame, there's no next frame to be found
    if (channel.size() == 1)
        return Frame{*channel.begin()};

    // Keep advancing until you find the current time point (between two keyframes)
    std::vector<Keyframe>::const_iterator last_key = channel.begin();
    std::vector<Keyframe>::const_iterator next_key = channel.begin()++;
    while (!(last_key->time <= time_elapsed && next_key->time >= time_elapsed))
    {
        last_key++;
        next_key++;
    }

    // If current time is right on a keyframe, there's no point in interpolating
    if (last_key->time == time_elapsed)
        return Frame{*last_key};
    if (next_key->time == time_elapsed)
        return Frame{*next_key};
}

/// The data returns can be added to the position, rotation and scaling of a WorldObj's Models
// std::map<std::string, Frame> const Animation::get_animated_frames(
//     nanoseconds const time_elapsed) const
// {
//     std::vector<Channel<Frame>> vec;
//     for (std::pair<std::string, Channel<Keyframe>> channel : this->channels)
//     {
//     }
// }
