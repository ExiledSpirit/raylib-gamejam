#include "LaunchSkillCheckResolverSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/SkillCheckResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"

#include "../../utils/PhaseHelper.hpp"
#include "../../utils/SkillCheckUtils.hpp"
#include "../../utils/LaunchSkillCheckUtils.hpp"

#include "../../utils/AudioHelper.hpp"
#include "../../const/AudioIds.hpp"

#include "../../factories/FloatingTextFactory.hpp"

void LaunchSkillCheckResolverSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();
    auto& stats =
        world.GetResource<PlayerStatsResource>();

    if(run.phase != RunPhase::SkillChecks)
    {
        return;
    }

    auto& skill =
        world.GetResource<SkillCheckResource>();

    if(!HasSkillCheckResult(skill))
    {
        return;
    }

    SkillCheckResult result =
        ConsumeSkillCheckResult(skill);

    if(result.context != SkillCheckContext::Launch)
    {
        return;
    }

    auto& strike =
        world.GetResource<PlayerStrikeResource>();

    switch(result.kind)
    {
        case SkillCheckTargetKind::Good:
        {
            CreateFloatingText(
                world,
                "Good",
                (Vector2){
                    .x=strike.playerPosition.x + 40.f,
                    .y=strike.playerPosition.y + 10.f
                },
                GREEN,
                1.5f
            );
            strike.skillCheckCounter++;

            AudioHelper::PlaySfx(AudioIds::SkillCheck, 0.5f, 1.0f);
            AudioHelper::PlaySfx(AudioIds::SkillCheckGood, 0.35f, 1.0f);
            AudioHelper::PlaySfx(AudioIds::SkillCheckBuildup, 0.3f, std::min(1.8f, 1.0f + (strike.skillCheckCounter * 0.2f)));

            strike.finalPowerMultiplier += stats.GetGoodPowerBonus();
            break;
        }

        case SkillCheckTargetKind::Great:
        {
            CreateFloatingText(
                world,
                "GREAT!!",
                (Vector2){
                    .x=strike.playerPosition.x + 45.f,
                    .y=strike.playerPosition.y + 5.f
                },
                ORANGE,
                1.5f
            );
            strike.skillCheckCounter++;

            AudioHelper::PlaySfx(AudioIds::SkillCheck, 0.5f, 1.0f);
            AudioHelper::PlaySfx(AudioIds::SkillCheckGreat, 0.5f, 1.0f);
            AudioHelper::PlaySfx(AudioIds::SkillCheckBuildup, 0.3f, std::min(1.8f, 1.0f + (strike.skillCheckCounter * 0.2f)));

            strike.finalPowerMultiplier += stats.GetGreatPowerBonus();
            break;
        }

        case SkillCheckTargetKind::ActivePower:
        {
            // Later:
            // ActivatePower(result.id);
            strike.finalPowerMultiplier += 0.20f;

            CreateFloatingText(
                world,
                result.label,
                (Vector2){
                    .x=strike.playerPosition.x + 45.f,
                    .y=strike.playerPosition.y + 5.f
                },
                RED,
                2.f,
                14
            );
            AudioHelper::PlaySfx(AudioIds::SkillCheck, 1.f, 1.0f);
            AudioHelper::PlaySfx(AudioIds::SkillCheckPower, 0.7f, 1.75f);

            RemoveSkillCheckTargetById(skill, result.id);
            return;
        }

        case SkillCheckTargetKind::Miss:
        default:
        {
            CreateFloatingText(
                world,
                "miss...",
                (Vector2){
                    .x=strike.playerPosition.x + 45.f,
                    .y=strike.playerPosition.y + 5.f
                },
                LIGHTGRAY,
                1.5f
            );
            AudioHelper::PlaySfx(AudioIds::SkillCheckMiss, 1.0f, 1.0f);
            break;
        }
    }

    int nextCheck =
        skill.currentCheck + 1;

    if(nextCheck >= skill.totalChecks)
    {
        AudioHelper::PlaySfx(AudioIds::SkillCheckBuildup, 0.f);
        EndSkillCheck(skill);
        SetRunPhase(run, RunPhase::LastStrikeAnimation);
        strike.skillCheckCounter = 0;
        return;
    }

    BeginSkillCheck(
        skill,
        SkillCheckContext::Launch,
        CreateLaunchSkillCheckTargets(),
        5.5f,
        nextCheck,
        skill.totalChecks
    );
}
