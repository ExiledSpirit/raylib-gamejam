#pragma once

#include <raylib.h>

struct DisplayResource {
    Vector2 internalResolution = {512, 288};
    Vector2 windowResolution = {1280, 720};
    float scale = 4.0f;
    Vector2 viewportOffset;
};
