#pragma once

#include <raylib.h>

struct IncomingBallResource
{
    Vector2 spawnPosition{52.0f, -12.0f};
    Vector2 position{52.0f, -12.0f};
    Vector2 velocity{0.0f, 90.0f};

    float radius = 4.0f;

    float groundY = 136.0f;

    bool active = false;
};
