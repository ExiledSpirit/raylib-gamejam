#pragma once

#include "../resources/RunResource.hpp"
#include "../resources/SkillCheckResource.hpp"
#include "../components/Ball.hpp"
#include "../components/BallPhysicsBody.hpp"

inline void SetRunPhase(
    RunResource& run,
    RunPhase phase
)
{
    run.phase = phase;
    run.phaseTimer = 0.0f;
}

inline void ResetSkillChecks(SkillCheckResource& skill)
{
    skill.currentEvent = 0;
    skill.needleAngle = 0.0f;

    skill.goodHits = 0;
    skill.greatHits = 0;
    skill.misses = 0;

    skill.active = true;
}

inline void DestroyActiveBalls(World& world)
{
    auto view = world.registry.view<Ball, BallPhysicsBody>();

    for(auto [entity, ball, physics] : view.each())
    {
        if(b2Body_IsValid(physics.bodyId))
        {
            b2DestroyBody(physics.bodyId);
        }

        world.registry.destroy(entity);
    }
}
