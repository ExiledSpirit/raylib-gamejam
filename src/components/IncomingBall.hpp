#pragma once

#include <raylib.h>

struct IncomingBall
{
    Vector2 velocity{0.0f, 180.0f};

    float radius = 5.0f;
    float groundY = 248.0f;

    bool active = true;

    bool ignoreInputThisFrame = true;
};
