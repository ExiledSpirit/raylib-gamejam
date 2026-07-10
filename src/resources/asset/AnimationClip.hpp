#pragma once
#include "raylib.h"
#include <vector>

struct AnimationClip
{
    Texture2D* texture;

    std::vector<Rectangle> frames;

    float frameDuration = 0.1f;

    bool loop = true;
};