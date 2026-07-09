#include "ShotEndSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/ShotScore.hpp"
#include "../../resources/RunResource.hpp"

#include <box2d/box2d.h>

#include <cmath>

static float Length(b2Vec2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

void ShotEndSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallRunning)
    {
        return;
    }

    auto view = world.registry.view<Ball, BallPhysicsBody, ShotScore>();

    for(auto [entity, ball, physicsBody, score] : view.each())
    {
        if(!b2Body_IsValid(physicsBody.bodyId))
        {
            continue;
        }

        b2Vec2 velocity =
            b2Body_GetLinearVelocity(physicsBody.bodyId);

        float speedMetersPerSecond =
            Length(velocity);

        // Tune this value later.
        if(speedMetersPerSecond > 0.15f)
        {
            return;
        }

        if(score.finalized)
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

        run.currentScore += score.finalScore;
        run.ballsRemaining--;

        b2DestroyBody(physicsBody.bodyId);

        world.registry.destroy(entity);

        if(run.currentScore >= run.requiredScore)
        {
            run.phase = RunPhase::MapWon;
        }
        else if(run.ballsRemaining <= 0)
        {
            run.phase = RunPhase::MapLost;
        }
        else
        {
            run.phase = RunPhase::WaitingForShot;
        }

        return;
    }
}