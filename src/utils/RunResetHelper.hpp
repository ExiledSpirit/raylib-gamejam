#pragma once

#include <core/World.hpp>

#include "../components/Ball.hpp"
#include "../components/BallPhysicsBody.hpp"
#include "../components/IncomingBall.hpp"

#include "../resources/RunResource.hpp"
#include "../resources/CampaignResource.hpp"
#include "../resources/EconomyResource.hpp"
#include "../resources/HudAnimationResource.hpp"
#include "../resources/RewardPopupResource.hpp"
#include "../resources/ShopResource.hpp"
#include "../resources/SkillCheckResource.hpp"
#include "../resources/PlayerPowerUpsResource.hpp"
#include "../resources/PlayerStatsResource.hpp"

#include "../utils/CampaignHelper.hpp"
#include "../utils/SkillCheckUtils.hpp"
#include "../utils/PhaseHelper.hpp"

#include <box2d/box2d.h>

#include <vector>

inline static void DestroyGameplayBalls(World& world)
{
    auto view =
        world.registry.view<Ball, BallPhysicsBody>();

    std::vector<entt::entity> entities;

    for(auto [entity, ball, physicsBody] : view.each())
    {
        (void)ball;

        if(b2Body_IsValid(physicsBody.bodyId))
        {
            b2DestroyBody(physicsBody.bodyId);
        }

        entities.push_back(entity);
    }

    for(entt::entity entity : entities)
    {
        if(world.registry.valid(entity))
        {
            world.registry.destroy(entity);
        }
    }
}

inline static void DestroyIncomingBalls(World& world)
{
    auto view =
        world.registry.view<IncomingBall>();

    std::vector<entt::entity> entities;

    for(auto entity : view)
    {
        entities.push_back(entity);
    }

    for(entt::entity entity : entities)
    {
        if(world.registry.valid(entity))
        {
            world.registry.destroy(entity);
        }
    }
}

inline void ResetGameRun(World& world)
{
    DestroyGameplayBalls(world);
    DestroyIncomingBalls(world);

    auto& campaign =
        world.GetResource<CampaignResource>();

    auto& economy =
        world.GetResource<EconomyResource>();

    auto& owned =
        world.GetResource<PlayerPowerUpsResource>();

    auto& stats =
        world.GetResource<PlayerStatsResource>();

    auto& run =
        world.GetResource<RunResource>();

    auto& hud =
        world.GetResource<HudAnimationResource>();

    auto& reward =
        world.GetResource<RewardPopupResource>();

    auto& shop =
        world.GetResource<ShopResource>();

    auto& skill =
        world.GetResource<SkillCheckResource>();

    campaign = CampaignResource{};

    economy.gold = 5;
    economy.powerGoldThisLevel = 0;

    owned.stacks.clear();
    // owned.stacks.push_back(PlayerPowerUpStack{.powerUpId="giant_ball", .count=24});
    // owned.stacks.push_back(PlayerPowerUpStack{.powerUpId="concentration_pill", .count=12});
    // owned.stacks.push_back(PlayerPowerUpStack{.powerUpId="anger", .count=30000});
    // owned.stacks.push_back(PlayerPowerUpStack{.powerUpId="high_risk_high_reward", .count=300000});
    // owned.stacks.push_back(PlayerPowerUpStack{.powerUpId="ball_printer", .count=400});

    stats.ResetToBase();

    run.currentScore = 0;
    run.requiredScore = CalculateRequiredScore(campaign);
    run.ballsRemaining = stats.GetBallsPerLevel();

    hud = HudAnimationResource{};
    reward = RewardPopupResource{};

    shop.slots.clear();
    shop.rerollCost = 1;

    // RecalculatePlayerStats(world);s

    EndSkillCheck(skill);

    SetRunPhase(
        run,
        RunPhase::WaitingToDropBall
    );
}

inline void ResetToMainMenuState(World& world)
{
    DestroyGameplayBalls(world);
    DestroyIncomingBalls(world);

    auto& run =
        world.GetResource<RunResource>();

    auto& skill =
        world.GetResource<SkillCheckResource>();

    EndSkillCheck(skill);

    SetRunPhase(
        run,
        RunPhase::WaitingToDropBall
    );
}