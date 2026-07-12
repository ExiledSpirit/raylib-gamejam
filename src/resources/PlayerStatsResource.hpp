#pragma once

#include <algorithm>

struct PlayerStatsResource
{
    // Balls
    int baseBallsPerLevel = 3;
    int extraBallsPerLevel = 0;

    // Skill checks
    int baseTotalSkillChecks = 3;
    int extraSkillChecks = 0;

    // Launch power
    float basePower = 5.0f;

    // First strike
    float goodFirstStrikeMultiplier = 1.0f;
    float perfectFirstStrikeMultiplier = 1.25f;

    // Skill check power gains.
    // These are added to PlayerStrikeResource::finalPowerMultiplier.
    float baseGoodPowerBonus = 2.f;
    float baseGreatPowerBonus = 4.f;

    // Passive item multipliers.
    // Example: +25% great bonus means greatPowerBonusMultiplier = 1.25f.
    float goodPowerBonusMultiplier = 1.0f;
    float greatPowerBonusMultiplier = 1.0f;

    int GetBallsPerLevel() const
    {
        return std::max(1, baseBallsPerLevel + extraBallsPerLevel);
    }

    int GetTotalSkillChecks() const
    {
        return std::max(0, baseTotalSkillChecks + extraSkillChecks);
    }

    float GetGoodPowerBonus() const
    {
        return baseGoodPowerBonus * goodPowerBonusMultiplier;
    }

    float GetGreatPowerBonus() const
    {
        return baseGreatPowerBonus * greatPowerBonusMultiplier;
    }
};