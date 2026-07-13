#pragma once

#include <raylib.h>

enum class StrikeQuality
{
    None,
    Good,
    Perfect
};

enum class StrikePhase
{
    Idle,
    FirstStrike,
    LastStrike,
    Finished
};

struct PlayerStrikeResource
{
    Vector2 playerPosition{144.0f, 216.0f};

    float facingRadians = -0.45f;

    Rectangle topZone{0.0f, 0.0f, 33.0f, 8.0f};
    Rectangle perfectZone{0.0f, 0.0f, 33.0f, 7.0f};
    Rectangle bottomZone{0.0f, 0.0f, 33.0f, 8.0f};

    StrikePhase phase = StrikePhase::Idle;
    StrikeQuality firstStrikeQuality = StrikeQuality::None;

    float firstStrikeTimer = 0.0f;
    float firstStrikeDuration = 0.35f;

    float lastStrikeTimer = 0.0f;
    float lastStrikeDuration = 0.22f;

    float basePower = 5.0f;
    float finalPowerMultiplier = 1.0f;
    Vector2 struckBallPosition{0.0f, 0.0f};

    int skillCheckCounter = 0;

    bool lastStrikeSfxPlayed = false;
};
