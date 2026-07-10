#pragma once

#include <raylib.h>

struct FallingBallResource
{
    Vector2 position{144.0f, -16.0f};
    Vector2 targetPosition{144.0f, 216.0f};

    float fallSpeed = 180.0f;

    float radius = 5.0f;
    bool active = false;
};
