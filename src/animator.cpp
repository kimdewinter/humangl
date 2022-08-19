#include "animator.h"

namespace
{
    nanoseconds const find_longest_duration(std::vector<Channel> const &channels)
    {
        nanoseconds longest = nanoseconds(0);
        for (Channel const channel : channels)
            for (Keyframe const keyframe : channel.keyframes)
                if (keyframe.time > longest)
                    longest = keyframe.time;
        return longest;
    }

    std::map<std::string, Channel> const map_channels(std::vector<Channel> const &channels)
    {
        std::map<std::string, Channel> map;
        for (Channel channel : channels)
            map.emplace(channel.model_name, channel);
        return map;
    }
}

Animation::Animation(std::string const animation_name, std::vector<Channel> const &channels)
    : animation_name{animation_name},
      duration{find_longest_duration(channels)},
      channels{map_channels(channels)}
{
}
