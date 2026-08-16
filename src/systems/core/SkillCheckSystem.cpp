#include "SkillCheckSystem.hpp"

#include "../../resources/SkillCheckResource.hpp"
#include "../../utils/SkillCheckUtils.hpp"

#include <ecs/resources/TimeResource.hpp>
#include <input/InputResource.hpp>

static SkillCheckResult EvaluateSkillCheck(
    const SkillCheckResource& skill
)
{
    TraceLog(LOG_INFO, "EVALUATING SKILLCHECK");
    SkillCheckResult result{};
    result.valid = true;
    result.context = skill.context;
    result.kind = SkillCheckTargetKind::Miss;
    result.id = "miss";
    result.label = "Miss";

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

        bestPriority = target.priority;

        result.kind = target.kind;
        result.id = target.id;
        result.label = target.label;
        result.itemIndex = target.itemIndex;
        result.goldCost = target.goldCost;
    }

    TraceLog(LOG_INFO, TextFormat("id = %s", result.id.c_str()));
    return result;
}
void SkillCheckSystem(World& world)
{
    auto& skill =
        world.GetResource<SkillCheckResource>();

    if(!skill.active)
    {
        return;
    }

    if(skill.pendingResult.valid)
    {
        return;
    }

    auto& time =
        world.GetResource<TimeResource>();

    auto& input =
        world.GetResource<InputResource>();

    if(skill.ignoreInputThisFrame)
    {
        skill.ignoreInputThisFrame = false;

        skill.needleAngle =
            WrapSkillCheckAngle(
                skill.needleAngle +
                skill.needleSpeed * time.deltaTime
            );

        return;
    }

    if(input.IsPressed("throw"))
    {
        skill.pendingResult =
            EvaluateSkillCheck(skill);

        return;
    }

    skill.needleAngle =
        WrapSkillCheckAngle(
            skill.needleAngle +
            skill.needleSpeed * time.deltaTime
        );
}