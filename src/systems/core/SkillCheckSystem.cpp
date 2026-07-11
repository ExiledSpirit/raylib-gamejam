#include "SkillCheckSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/SkillCheckResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"
#include "../../utils/PhaseHelper.hpp"

#include <ecs/resources/TimeResource.hpp>
#include <input/InputResource.hpp>

#include "../../const/AudioIds.hpp"
#include "../../utils/AudioHelper.hpp"

#include <cmath>

// static constexpr float PI = 3.1415926535f;
static constexpr float TAU = PI * 2.0f;

static float WrapAngle(float angle)
{
    while(angle < 0.0f)
    {
        angle += TAU;
    }

    while(angle >= TAU)
    {
        angle -= TAU;
    }

    return angle;
}

static float AngleDistance(float a, float b)
{
    float diff = std::fabs(WrapAngle(a) - WrapAngle(b));

    if(diff > PI)
    {
        diff = TAU - diff;
    }

    return diff;
}

static void StartNextSkillCheck(SkillCheckResource& skill)
{
    skill.currentEvent++;
    // skill.needleAngle = 0.0f;

    // Later you can randomize this.
    skill.zoneCenterAngle = 1.0f + 0.7f * static_cast<float>(skill.currentEvent);
    skill.zoneCenterAngle = WrapAngle(skill.zoneCenterAngle);
}

void SkillCheckSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::SkillChecks)
    {
        return;
    }

    auto& time = world.GetResource<TimeResource>();
    auto& input = world.GetResource<InputResource>();
    auto& skill = world.GetResource<SkillCheckResource>();
    auto& strike = world.GetResource<PlayerStrikeResource>();

    skill.needleAngle =
        WrapAngle(skill.needleAngle + skill.needleSpeed * time.deltaTime);

    if(input.IsPressed("throw"))
    {
        // later change dist based on current needle angle
        float dist =
            AngleDistance(skill.needleAngle, skill.zoneCenterAngle);

        if(dist <= skill.greatZoneSize * 0.5f)
        {
            AudioHelper::PlaySfx(AudioIds::SkillCheck, 3.0f, 2.5f);

            skill.greatHits++;
            strike.finalPowerMultiplier += skill.powerPerGreat;
        }
        else if(dist <= skill.goodZoneSize * 0.5f)
        {
            AudioHelper::PlaySfx(AudioIds::SkillCheck, 3.0f, 1.0f);
            skill.goodHits++;
            strike.finalPowerMultiplier += skill.powerPerGood;
        }
        else
        {
            skill.misses++;
        }

        // For now using LastStrike on Skillcheck
        AudioHelper::PlaySfx(AudioIds::LastStrike, 1.0f, 0.5f + skill.greatHits * 0.6f + skill.goodHits * 0.6f);

        // TODO: you should remove hardcoded later
        if(skill.currentEvent + 1 >= skill.totalEvents)
        {
            skill.active = false;
            SetRunPhase(run, RunPhase::LastStrikeAnimation);
        }
        else
        {
            StartNextSkillCheck(skill);
        }
    }
}
