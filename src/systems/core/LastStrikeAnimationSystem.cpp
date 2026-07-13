#include "LastStrikeAnimationSystem.hpp"
#include <ecs/resources/TimeResource.hpp>
#include "../../resources/StrikeZonesResource.hpp"
#include "../../resources/RunResource.hpp"
#include "../../utils/PhaseHelper.hpp"
#include "../../factories/LaunchedBallFactory.hpp"

#include "../../const/AudioIds.hpp"
#include "../../utils/AudioHelper.hpp"

void LastStrikeAnimationSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::LastStrikeAnimation)
    {
        return;
    }

    auto& time = world.GetResource<TimeResource>();
    auto& strike = world.GetResource<PlayerStrikeResource>();

    strike.lastStrikeTimer += time.deltaTime;

    if (!strike.lastStrikeSfxPlayed) {
        // player animation = last_strike_animation
        // AudioHelper::PlaySfx(AudioIds::LastStrike);
        strike.lastStrikeSfxPlayed = true;
    }

    if(strike.lastStrikeTimer < strike.lastStrikeDuration)
    {
        return;
    }

    
    AudioHelper::PlaySfx(AudioIds::LastStrike, 0.6f, 1.f);
    CreateLaunchedBallFromStrike(world);
    SetRunPhase(run, RunPhase::BallRunning);

    float finalPower =
        strike.basePower * strike.finalPowerMultiplier;

    AudioHelper::PlayMusic(AudioIds::MainSoundTrack, 0.6f);
    run.phase = RunPhase::BallRunning;
}