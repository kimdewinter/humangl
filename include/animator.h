#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include "types.h"

using namespace std::chrono;

struct Keyframe
{
    nanoseconds const time = nanoseconds(0); // Time since beginning of animation
    vec3 const translations = {0.0, 0.0, 0.0};
    vec3 const rotations = {0.0, 0.0, 0.0};
    vec3 const scalings = {0.0, 0.0, 0.0};
};

/// Contains all keyframes for a given Model
struct Channel
{
    std::string const model_name = "";
    std::vector<Keyframe> keyframes = {Keyframe{}};
};

/// Data repository for an animation, only constant members
/// to use, simply construct the class, and call the getter to receive transformation matrixes
class Animation
{
public:
    Animation(std::string const animation_name, std::vector<Channel> const &channels);
    std::map<std::string, mat4> const get_animated_mat4s(nanoseconds const time_elapsed) const;

private:
    std::string const animation_name;
    nanoseconds const duration;
    std::map<std::string, Channel> const channels;
};
