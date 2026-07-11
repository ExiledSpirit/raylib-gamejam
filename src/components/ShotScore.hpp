#pragma once

#include <raylib.h>

struct ShotScore
{
    Vector2 previousPosition{};

    float distanceMeters = 0.0f;

    int chips = 0;
    int lastDisplayedChips = 0;

    int wallHits = 0;
    int mult = 1;
    int finalScore = 0;

    bool initialized = false;
    bool finalized = false;
};