#include "PhysicsStepSystem.hpp"

#include "PhysicsWorldResource.hpp"

#include "../ecs/resources/TimeResource.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

void PhysicsStepSystem(World& world)
{
    auto& physics = world.GetResource<PhysicsWorldResource>();
    auto& time = world.GetResource<TimeResource>();

    if(!b2World_IsValid(physics.worldId))
    {
        return;
    }

    physics.accumulator += time.deltaTime;

    while(physics.accumulator >= physics.fixedTimeStep)
    {
        b2World_Step(
            physics.worldId,
            physics.fixedTimeStep,
            physics.subStepCount
        );

        physics.accumulator -= physics.fixedTimeStep;
    }
}
