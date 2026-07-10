#pragma once

#include "../../resources/asset/AssetManager.hpp"

struct AnimationPlayer
{
    AnimationClip* currentClip = nullptr;
    int currentFrame = 0;
    float timer = 0.f;
    bool playing = true;
};