#pragma once

#include "../resources/SkillCheckResource.hpp"

#include <raylib.h>

#include <vector>

inline std::vector<SkillCheckTarget> CreateLaunchSkillCheckTargets()
{
    float center =
        static_cast<float>(GetRandomValue(0, 6283)) / 1000.0f;

    std::vector<SkillCheckTarget> targets;

    SkillCheckTarget good{};
    good.id = "good";
    good.label = "Good";
    good.kind = SkillCheckTargetKind::Good;
    good.centerAngle = center;
    good.size = 0.72f;
    good.priority = 1;
    good.color = BLANK;
    good.outlined = true;
    good.outlineColor = WHITE;
    good.outlineThickness = .0f;

    targets.push_back(good);

    SkillCheckTarget great{};
    great.id = "great";
    great.label = "Great";
    great.kind = SkillCheckTargetKind::Great;
    great.centerAngle = center +0.40;
    great.size = 0.22f;
    great.priority = 2;
    great.color = ORANGE;
    great.outlined = false;

    targets.push_back(great);

    return targets;
}
