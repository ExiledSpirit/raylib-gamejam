#pragma once

#include <core/World.hpp>

#include "../resources/PlayerStatsResource.hpp"
#include "../resources/PlayerPowerUpsResource.hpp"
#include "../resources/PowerUpDatabaseResource.hpp"

inline const PowerUpDefinition* FindPowerUp(
    const PowerUpDatabaseResource& database,
    const std::string& id
)
{
    for(const PowerUpDefinition& definition : database.definitions)
    {
        if(definition.id == id)
        {
            return &definition;
        }
    }

    return nullptr;
}

inline static void ApplyPowerUpModifier(
    PlayerStatsResource& stats,
    const PowerUpModifier& modifier,
    int count
)
{
    float value =
        modifier.value * static_cast<float>(count);

    switch(modifier.type)
    {
        case PowerUpModifierType::ExtraBalls:
        {
            stats.ballsPerLevel += static_cast<int>(value);
            break;
        }

        case PowerUpModifierType::ExtraSkillChecks:
        {
            stats.totalSkillChecks += static_cast<int>(value);
            break;
        }

        case PowerUpModifierType::GoodPowerBonusMultiplier:
        {
            stats.goodPowerBonusMultiplier += value;
            break;
        }

        case PowerUpModifierType::GreatPowerBonusMultiplier:
        {
            stats.greatPowerBonusMultiplier += value;
            break;
        }

        case PowerUpModifierType::SkillCheckSizeMultiplier:
        {
            stats.skillCheckSizeMultiplier += value;
            break;
        }

        case PowerUpModifierType::BasePowerMultiplier:
        {
            stats.powerMultiplier += value;
            break;
        }

        case PowerUpModifierType::BallSizeMultiplier:
        {
            stats.ballSizeMultiplier += value;
            break;
        }

        case PowerUpModifierType::ExtraLaunchedBalls:
        {
            stats.extraLaunchedBalls += static_cast<int>(value);
            break;
        }

        case PowerUpModifierType::MultiBallAngleStep:
        {
            stats.multiBallAngleStep += value;
            break;
        }

        case PowerUpModifierType::ExplosionChanceOnWallBounce:
        {
            stats.explosionChanceOnWallBounce += value;
            break;
        }

        case PowerUpModifierType::ExplosionVelocityMultiplier:
        {
            stats.explosionVelocityMultiplier += value;
            break;
        }
    }
}

inline static void RecalculatePlayerStats(World& world)
{
    auto& stats =
        world.GetResource<PlayerStatsResource>();

    auto& owned =
        world.GetResource<PlayerPowerUpsResource>();

    auto& database =
        world.GetResource<PowerUpDatabaseResource>();

    stats.ResetToBase();

    for(const PlayerPowerUpStack& stack : owned.stacks)
    {
        const PowerUpDefinition* power =
            FindPowerUp(database, stack.powerUpId);

        if(power == nullptr)
        {
            continue;
        }

        if(power->type != PowerUpType::Passive)
        {
            continue;
        }

        for(const PowerUpModifier& modifier : power->modifiers)
        {
            ApplyPowerUpModifier(
                stats,
                modifier,
                stack.count
            );
        }
    }
}