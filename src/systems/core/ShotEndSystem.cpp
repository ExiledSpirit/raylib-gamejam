#include "ShotEndSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/ShotScore.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/HudAnimationResource.hpp"

#include "../../utils/PhaseHelper.hpp"

#include <box2d/box2d.h>

void ShotEndSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallRunning)
    {
        return;
    }

    auto& hud =
        world.GetResource<HudAnimationResource>();

    auto view =
        world.registry.view<Ball, BallPhysicsBody, ShotScore>();

    for(auto [entity, ball, physicsBody, score] : view.each())
    {
        (void)ball;

        if(score.finalized)
        {
            return;
        }

        if(!b2Body_IsValid(physicsBody.bodyId))
        {
            continue;
        }

        constexpr float stopDelay = 0.25f;

        if(score.slowTimer < stopDelay)
        {
            return;
        }

        score.chips =
            static_cast<int>(score.distanceMeters);

        score.mult =
            1 + score.wallHits;

        score.finalScore =
            score.chips * score.mult;

        score.finalized = true;

        int finalShotScore =
            score.finalScore;

        run.ballsRemaining--;

        hud.payout.active = true;
        hud.payout.applied = false;
        hud.payout.amount = finalShotScore;
        hud.payout.timer = 0.0f;
        hud.payout.duration = 0.65f;

        hud.payout.startPosition =
            Vector2{40.0f, 110.0f};

        hud.payout.targetPosition =
            Vector2{128.0f, 88.0f};

        hud.payout.position =
            hud.payout.startPosition;

        hud.payoutPulse.timer =
            hud.payoutPulse.duration;

        b2DestroyBody(physicsBody.bodyId);

        world.registry.destroy(entity);

        SetRunPhase(run, RunPhase::ShotFinished);

        return;
    }
}