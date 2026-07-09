#pragma once

#include <raylib.h>

struct DisplayResource
{
    int internalWidth = 320;
    int internalHeight = 180;

    int windowWidth = 720;
    int windowHeight = 720;

    float scale = 1.f;

    Vector2 viewportOffset{0.0f, 0.0f};
    Vector2 viewportSize{320.0f, 180.0f};
};
