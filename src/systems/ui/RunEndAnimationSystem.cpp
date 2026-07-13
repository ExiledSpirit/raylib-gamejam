#include "RunEndAnimationSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/RunEndAnimationResource.hpp"

#include "../../utils/AudioHelper.hpp"
#include "../../utils/LevelRewardUtils.hpp"
#include "../../utils/PhaseHelper.hpp"

#include "../../const/AudioIds.hpp"

#include <ecs/resources/TimeResource.hpp>

void RunEndAnimationSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    auto& animation =
        world.GetResource<RunEndAnimationResource>();

    auto& time =
        world.GetResource<TimeResource>();

    if(animation.previousPhase != run.phase)
    {
        animation.previousPhase = run.phase;
        animation.timer = 0.0f;
        animation.loseMusicStarted = false;
        animation.winFinished = false;
    }

    if(run.phase != RunPhase::MapLost &&
       run.phase != RunPhase::MapWon)
    {
        return;
    }

    animation.timer += time.deltaTime;

    if(run.phase == RunPhase::MapLost)
    {
        if(!animation.loseMusicStarted)
        {
            animation.loseMusicStarted = true;

            AudioHelper::StopMusic(AudioIds::StoreSoundTrack);

            AudioHelper::StartMusicPitchTransition(
                AudioIds::MainSoundTrack,
                0.55f,
                2.3f
            );
        }

        return;
    }

    if(run.phase == RunPhase::MapWon)
    {
        constexpr float endlessAnimationDuration = 2.15f;

        if(!animation.winFinished &&
           animation.timer >= endlessAnimationDuration)
        {
            animation.winFinished = true;

            OpenLevelRewardPopup(world);

            SetRunPhase(
                run,
                RunPhase::LevelReward
            );
        }
    }
}
