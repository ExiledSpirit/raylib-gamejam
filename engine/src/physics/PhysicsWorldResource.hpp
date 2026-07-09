#pragma once

#include <box2d/box2d.h>

struct PhysicsWorldResource
{
    b2WorldId worldId = b2_nullWorldId;

    float fixedTimeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    float accumulator = 0.0f;
};
