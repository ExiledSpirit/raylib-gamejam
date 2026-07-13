#pragma once

#include "../resources/PlayerPowerUpsResource.hpp"

#include <string>

inline int GetPowerUpCount(
    const PlayerPowerUpsResource& owned,
    const std::string& powerUpId
)
{
    for(const PlayerPowerUpStack& stack : owned.stacks)
    {
        if(stack.powerUpId == powerUpId)
        {
            return stack.count;
        }
    }

    return 0;
}

inline void AddPowerUp(
    PlayerPowerUpsResource& owned,
    const std::string& powerUpId,
    int amount = 1
)
{
    for(PlayerPowerUpStack& stack : owned.stacks)
    {
        if(stack.powerUpId == powerUpId)
        {
            stack.count += amount;
            return;
        }
    }

    owned.stacks.push_back(
        PlayerPowerUpStack{
            powerUpId,
            amount
        }
    );
}

inline std::string GetPowerUpStackSuffix(int count)
{
    if(count <= 0)
    {
        return "";
    }

    if(count <= 3)
    {
        return std::string(static_cast<size_t>(count), '+');
    }

    return "+" + std::to_string(count);
}

inline std::string GetPowerUpDisplayName(
    const std::string& baseName,
    int ownedCount
)
{
    std::string suffix =
        GetPowerUpStackSuffix(ownedCount);

    if(suffix.empty())
    {
        return baseName;
    }

    return baseName + " " + suffix;
}
