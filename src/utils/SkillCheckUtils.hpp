#pragma once

#include "../resources/SkillCheckResource.hpp"

#include <raylib.h>

#include <cmath>
#include <vector>

static constexpr float SKILL_CHECK_PI = 3.14159265359f;
static constexpr float SKILL_CHECK_TAU = 6.28318530718f;

inline float WrapSkillCheckAngle(float angle)
{
    while(angle < 0.0f)
    {
        angle += SKILL_CHECK_TAU;
    }

    while(angle >= SKILL_CHECK_TAU)
    {
        angle -= SKILL_CHECK_TAU;
    }

    return angle;
}

inline float SkillCheckAngleDistance(float a, float b)
{
    float diff =
        std::fmod(a - b + SKILL_CHECK_PI, SKILL_CHECK_TAU);

    if(diff < 0.0f)
    {
        diff += SKILL_CHECK_TAU;
    }

    return std::fabs(diff - SKILL_CHECK_PI);
}

inline void BeginSkillCheck(
    SkillCheckResource& skill,
    SkillCheckContext context,
    const std::vector<SkillCheckTarget>& targets,
    float needleSpeed,
    int currentCheck,
    int totalChecks
)
{
    skill.active = true;
    skill.ignoreInputThisFrame = true;

    skill.context = context;
    skill.targets = targets;

    // skill.needleAngle =
    //     static_cast<float>(GetRandomValue(0, 6283)) / 1000.0f;

    skill.needleSpeed = needleSpeed;

    skill.currentCheck = currentCheck;
    skill.totalChecks = totalChecks;

    skill.pendingResult = SkillCheckResult{};
}

inline bool HasSkillCheckResult(const SkillCheckResource& skill)
{
    return skill.pendingResult.valid;
}

inline SkillCheckResult ConsumeSkillCheckResult(SkillCheckResource& skill)
{
    SkillCheckResult result =
        skill.pendingResult;

    skill.pendingResult =
        SkillCheckResult{};

    return result;
}

inline void EndSkillCheck(SkillCheckResource& skill)
{
    skill.active = false;
    skill.ignoreInputThisFrame = false;
    skill.pendingResult = SkillCheckResult{};
    skill.targets.clear();
    skill.context = SkillCheckContext::None;
}

inline void ClearSkillCheckResult(SkillCheckResource& skill)
{
    skill.pendingResult = SkillCheckResult{};
}

inline void RemoveSkillCheckTargetById(
    SkillCheckResource& skill,
    const std::string& id
)
{
    skill.targets.erase(
        std::remove_if(
            skill.targets.begin(),
            skill.targets.end(),
            [&](const SkillCheckTarget& target)
            {
                return target.id == id;
            }
        ),
        skill.targets.end()
    );
}

inline void ReplaceSkillCheckTargetById(
    SkillCheckResource& skill,
    const std::string& id,
    const SkillCheckTarget& replacement
)
{
    for(SkillCheckTarget& target : skill.targets)
    {
        if(target.id == id)
        {
            target = replacement;
            return;
        }
    }
}

inline const SkillCheckTarget* GetCurrentHoveredSkillCheckTarget(
    const SkillCheckResource& skill
)
{
    const SkillCheckTarget* best = nullptr;
    int bestPriority = -999999;

    for(const SkillCheckTarget& target : skill.targets)
    {
        float distance =
            SkillCheckAngleDistance(
                skill.needleAngle,
                target.centerAngle
            );

        bool inside =
            distance <= target.size * 0.5f;

        if(!inside)
        {
            continue;
        }

        if(target.priority < bestPriority)
        {
            continue;
        }

        best = &target;
        bestPriority = target.priority;
    }

    return best;
}
