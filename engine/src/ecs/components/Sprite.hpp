#pragma once
#include <raylib.h>

struct Sprite
{
    Texture2D* albedoTexture = nullptr;

    Rectangle source =
    {
        0,
        0,
        8,
        8
    };

    Vector2 pivot;

    float scale = 1.f;
    bool flipX = false;
};