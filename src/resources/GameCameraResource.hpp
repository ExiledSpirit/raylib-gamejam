#pragma once

#include <raylib.h>

struct GameCameraResource
{
    Vector2 target{0.0f, 0.0f};
    Vector2 position{0.0f, 0.0f};

    float zoom = 1.0f;
    float targetZoom = 1.0f;

    float speed = 12.0f;
};
