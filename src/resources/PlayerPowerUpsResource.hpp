#pragma once

#include <string>
#include <vector>

struct PlayerPowerUpStack
{
    std::string powerUpId;
    int count = 0;
};

struct PlayerPowerUpsResource
{
    std::vector<PlayerPowerUpStack> stacks;
};
