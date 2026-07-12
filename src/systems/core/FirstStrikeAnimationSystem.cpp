#include "FirstStrikeAnimationSystem.hpp"
#include <ecs/resources/TimeResource.hpp>
#include "../../utils/PhaseHelper.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"
#include "../../utils/AudioHelper.hpp"
#include "../../const/AudioIds.hpp"
#include "../../resources/SkillCheckResource.hpp"
#include "../../utils/SkillCheckUtils.hpp"
#include "../../utils/LaunchSkillCheckUtils.hpp"

void FirstStrikeAnimationSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();
    auto& time = world.GetResource<TimeResource>();
    auto& strike = world.GetResource<PlayerStrikeResource>();
    auto& stats = world.GetResource<PlayerStatsResource>();

    run.phaseTimer += time.deltaTime;

    switch(run.phase)
    {
        case RunPhase::FirstStrikeAnimation:
        {
            if(run.phaseTimer >= strike.firstStrikeDuration)
            {
                auto& skill = world.GetResource<SkillCheckResource>();

                BeginSkillCheck(
                    skill,
                    SkillCheckContext::Launch,
                    CreateLaunchSkillCheckTargets(),
                    5.5f,
                    0,
                    stats.GetTotalSkillChecks()
                );

                SetRunPhase(run, RunPhase::SkillChecks);
            }

            break;
        }

        case RunPhase::BallMissed:
        {
            if(run.phaseTimer >= 1.0f)
            {
                SetRunPhase(run, RunPhase::WaitingToDropBall);
            }

            break;
        }

        case RunPhase::LastStrikeAnimation:
        {
            if(run.phaseTimer >= strike.lastStrikeDuration)
            {
                // Later: launch Box2D ball here or call LaunchBall(world)
                SetRunPhase(run, RunPhase::BallRunning);
            }

            break;
        }

        default:
            break;
    }
}