#include "BallLowSpeedDampingSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/ShotScore.hpp"
#include "../../resources/RunResource.hpp"

#include <ecs/resources/TimeResource.hpp>

#include <box2d/box2d.h>

#include <cmath>

static float Length(b2Vec2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

void BallLowSpeedDampingSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallRunning)
    {
        return;
    }

    auto& time = world.GetResource<TimeResource>();

    auto view =
        world.registry.view<Ball, BallPhysicsBody, ShotScore>();

    for(auto [entity, ball, physics, score] : view.each())
    {
        (void)entity;
        (void)ball;

        if(!b2Body_IsValid(physics.bodyId))
        {
            continue;
        }

        b2Vec2 velocity =
            b2Body_GetLinearVelocity(physics.bodyId);

        float speed =
            Length(velocity);

        constexpr float slowSpeed = 2.5f;
        constexpr float verySlowSpeed = 0.45f;

        constexpr float minExtraDamping = 4.0f;
        constexpr float maxExtraDamping = 18.0f;

        if(speed < slowSpeed)
        {
            float slowAmount =
                1.0f - (speed / slowSpeed);

            if(slowAmount < 0.0f)
            {
                slowAmount = 0.0f;
            }

            if(slowAmount > 1.0f)
            {
                slowAmount = 1.0f;
            }

            float damping =
                minExtraDamping +
                slowAmount * (maxExtraDamping - minExtraDamping);

            float factor =
                std::exp(-damping * time.deltaTime);

            b2Body_SetLinearVelocity(
                physics.bodyId,
                b2Vec2{
                    velocity.x * factor,
                    velocity.y * factor
                }
            );
        }

        if(speed < verySlowSpeed)
        {
            score.slowTimer += time.deltaTime;
        }
        else
        {
            score.slowTimer = 0.0f;
        }
    }
}
