// #pragma once

// enum class SkillCheckResult
// {
//     None,
//     Miss,
//     Good,
//     Great
// };

// struct SkillCheckResource
// {
//     int totalEvents = 2;
//     int currentEvent = 0;

//     float needleAngle = 0.0f;
//     float needleSpeed = 5.0f;

//     float zoneCenterAngle = 1.5f;
//     float goodZoneSize = 0.55f;
//     float greatZoneSize = 0.16f;

//     float powerPerGood = 2.0f;
//     float powerPerGreat = 5.0f;

//     int goodHits = 0;
//     int greatHits = 0;
//     int misses = 0;

//     bool active = false;

//     // TODO: powerup skillcheck list
// };
#pragma once

#include <raylib.h>

#include <string>
#include <vector>

enum class SkillCheckContext
{
    None,
    Launch,
    Shop
};

enum class SkillCheckTargetKind
{
    Miss,

    Good,
    Great,
    ActivePower,

    ShopItem,
    Reroll,
    Exit
};

struct SkillCheckTarget
{
    std::string id;
    std::string label;

    SkillCheckTargetKind kind = SkillCheckTargetKind::Good;

    // Radians.
    float centerAngle = 0.0f;
    float size = 0.5f;

    int priority = 0;

    int itemIndex = -1;
    int goldCost = 0;

    Color color = WHITE;

    bool outlined = false;
    Color outlineColor = WHITE;
    float outlineThickness = 2.0f;
};

struct SkillCheckResult
{
    bool valid = false;

    SkillCheckContext context = SkillCheckContext::None;
    SkillCheckTargetKind kind = SkillCheckTargetKind::Miss;

    std::string id = "miss";
    std::string label = "Miss";

    int itemIndex = -1;
    int goldCost = 0;
};

struct SkillCheckResource
{
    bool active = false;
    bool ignoreInputThisFrame = false;

    SkillCheckContext context = SkillCheckContext::None;

    Vector2 center{320.0f, 180.0f};

    // DBD-like ring.
    float innerRadius = 42.0f;
    float outerRadius = 56.0f;

    Color ringColor{255, 255, 255, 50};
    Color needleColor{255, 255, 255, 255};

    float needleAngle = 0.0f;
    float needleSpeed = 5.5f;
    float needleWidth = 0.055f;

    int currentCheck = 0;
    int totalChecks = 0;

    std::vector<SkillCheckTarget> targets;

    SkillCheckResult pendingResult{};
};