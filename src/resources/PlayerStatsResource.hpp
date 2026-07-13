#pragma once

#include <algorithm>

struct PlayerStatsResource
{
    int baseBallsPerLevel = 3;
    int ballsPerLevel = 3;

    float goodFirstStrikeMultiplier = 1.0f;
    float perfectFirstStrikeMultiplier = 1.25f;

    int baseTotalSkillChecks = 3;
    int totalSkillChecks = 3;

    float basePower = 5.0f;
    float powerMultiplier = 1.0f;

    float baseGoodPowerBonus = 2.f;
    float goodPowerBonusMultiplier = 1.0f;

    float baseGreatPowerBonus = 3.f;
    float greatPowerBonusMultiplier = 1.0f;

    float skillCheckSizeMultiplier = 1.0f;

    float baseBallRadiusMeters = 0.5f;
    float ballSizeMultiplier = 1.0f;

    int extraLaunchedBalls = 0;
    float multiBallAngleStep = 0.22f;

    float explosionChanceOnWallBounce = 0.0f;
    float explosionVelocityMultiplier = 1.0f;

    void ResetToBase()
    {
        ballsPerLevel = baseBallsPerLevel;
        totalSkillChecks = baseTotalSkillChecks;

        powerMultiplier = 1.0f;
        goodPowerBonusMultiplier = 1.0f;
        greatPowerBonusMultiplier = 1.0f;
        skillCheckSizeMultiplier = 1.0f;

        ballSizeMultiplier = 1.0f;
        extraLaunchedBalls = 0;
        multiBallAngleStep = 0.22f;

        explosionChanceOnWallBounce = 0.0f;
        explosionVelocityMultiplier = 1.0f;
    }

    int GetBallsPerLevel() const
    {
        return std::max(1, ballsPerLevel);
    }

    int GetTotalSkillChecks() const
    {
        return std::max(1, totalSkillChecks);
    }

    float GetBasePower() const
    {
        return basePower * powerMultiplier;
    }

    float GetGoodPowerBonus() const
    {
        return baseGoodPowerBonus * goodPowerBonusMultiplier;
    }

    float GetGreatPowerBonus() const
    {
        return baseGreatPowerBonus * greatPowerBonusMultiplier;
    }

    float GetBallRadiusMeters() const
    {
        return std::max(0.2f, baseBallRadiusMeters * ballSizeMultiplier);
    }

    int GetLaunchedBallCount() const
    {
        return std::max(1, 1 + extraLaunchedBalls);
    }

    bool HasExplosiveBounce() const
    {
        return explosionChanceOnWallBounce > 0.0f;
    }
};