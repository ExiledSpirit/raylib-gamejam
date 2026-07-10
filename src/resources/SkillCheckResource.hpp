#pragma once

enum class SkillCheckResult
{
    None,
    Miss,
    Good,
    Great
};

struct SkillCheckResource
{
    int totalEvents = 3;
    int currentEvent = 0;

    float needleAngle = 0.0f;
    float needleSpeed = 5.0f;

    float zoneCenterAngle = 1.5f;
    float goodZoneSize = 0.55f;
    float greatZoneSize = 0.16f;

    float powerPerGood = 0.15f;
    float powerPerGreat = 0.35f;

    int goodHits = 0;
    int greatHits = 0;
    int misses = 0;

    bool active = false;

    // TODO: powerup skillcheck list
};