#pragma once

#include <raylib.h>

struct HudPulse
{
    float timer = 0.0f;
    float duration = 0.18f;
    float strength = 0.35f;
};

struct HudScorePayout
{
    bool active = false;
    bool applied = false;

    int amount = 0;

    Vector2 startPosition{40.0f, 110.0f};
    Vector2 targetPosition{128.0f, 88.0f};
    Vector2 position{40.0f, 110.0f};

    float timer = 0.0f;
    float duration = 0.65f;
};

struct HudAnimationResource
{
    int previousChips = 0;
    int previousMult = 0;
    int previousScore = 0;
    int previousBalls = 0;

    HudPulse chipsPulse;
    HudPulse multPulse;
    HudPulse scorePulse;
    HudPulse ballsPulse;
    HudPulse payoutPulse;

    HudScorePayout payout;

    float time = 0.0f;

    float barShakeTimer = 0.0f;
    float barShakeDuration = 0.75f;
    float barShakeStrength = 0.0f;
};