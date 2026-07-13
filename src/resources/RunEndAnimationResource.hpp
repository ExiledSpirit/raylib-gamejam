#pragma once

#include "RunResource.hpp"

struct RunEndAnimationResource
{
    RunPhase previousPhase = RunPhase::WaitingToDropBall;

    float timer = 0.0f;

    bool loseMusicStarted = false;
    bool winFinished = false;
};
