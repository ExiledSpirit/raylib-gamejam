#include "ShotEndSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/ShotScore.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/HudAnimationResource.hpp"

#include "../../utils/PhaseHelper.hpp"

#include <box2d/box2d.h>
#include <raylib.h>

#include <vector>

void ShotEndSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallRunning)
    {
        return;
    }

    auto view =
        world.registry.view<Ball, BallPhysicsBody, ShotScore>();

    constexpr float stopDelay = 0.25f;

    bool hasAnyBall = false;
    bool allBallsStopped = true;

    int totalShotScore = 0;

    std::vector<entt::entity> ballsToDestroy;

    bool shouldStopBalls = IsKeyPressed(KEY_F1);

    for(auto [entity, ball, physicsBody, score] : view.each())
    {
        (void)ball;

        if (shouldStopBalls) {
            allBallsStopped = true;
            continue;
        }

        hasAnyBall = true;

        if(!b2Body_IsValid(physicsBody.bodyId))
        {
            ballsToDestroy.push_back(entity);
            continue;
        }

        if(score.slowTimer < stopDelay)
        {
            allBallsStopped = false;
        }

        score.chips = score.distanceMeters;

        score.mult =
            1 + score.wallHits;

        score.finalScore =
            score.chips * score.mult;

        totalShotScore += score.finalScore;

        ballsToDestroy.push_back(entity);
    }

    if(!hasAnyBall)
    {
        return;
    }

    if(!allBallsStopped)
    {
        return;
    }

    auto& hud =
        world.GetResource<HudAnimationResource>();

    run.ballsRemaining--;

    hud.payout.active = true;
    hud.payout.applied = false;
    hud.payout.amount = totalShotScore;
    hud.payout.timer = 0.0f;
    hud.payout.duration = 0.65f;

    hud.payout.startPosition =
        Vector2{60.0f, 200.0f};

    hud.payout.targetPosition =
        Vector2{58.0f, 142.0f};

    hud.payout.position =
        hud.payout.startPosition;

    hud.payoutPulse.timer =
        hud.payoutPulse.duration;

    for(entt::entity entity : ballsToDestroy)
    {
        if(!world.registry.valid(entity))
        {
            continue;
        }

        auto* physicsBody =
            world.registry.try_get<BallPhysicsBody>(entity);

        if(physicsBody != nullptr &&
           b2Body_IsValid(physicsBody->bodyId))
        {
            b2DestroyBody(physicsBody->bodyId);
        }

        world.registry.destroy(entity);
    }

    SetRunPhase(run, RunPhase::ShotFinished);
}