#pragma once

#include <raylib.h>

struct ShotScore
{
    float distanceMeters = 0.0f;
    Vector2 previousPosition{};

    int wallHits = 0;
    float wallHitCooldown = 0.0f;

    int chips = 0;
    int mult = 1;
    int finalScore = 0;

    bool initialized = false;
    bool finalized = false;
};
