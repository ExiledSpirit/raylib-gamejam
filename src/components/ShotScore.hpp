#pragma once

#include <raylib.h>

struct ShotScore
{
    Vector2 previousPosition{};

    float distanceMeters = 0.0f;

    __int128_t chips = 0;
    __int128_t lastDisplayedChips = 0;

    __int128_t wallHits = 0;
    __int128_t mult = 1;
    __int128_t finalScore = 0;

    float slowTimer = 0.0f;
    bool initialized = false;
    bool finalized = false;

    bool onFire = false;
};