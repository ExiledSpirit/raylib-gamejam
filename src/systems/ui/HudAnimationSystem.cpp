#include "HudAnimationSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/ShotScore.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/HudAnimationResource.hpp"

#include <ecs/resources/TimeResource.hpp>

static const ShotScore* GetCurrentShotScore(World& world)
{
    auto view = world.registry.view<Ball, ShotScore>();

    for(auto [entity, ball, score] : view.each())
    {
        (void)entity;
        (void)ball;

        return &score;
    }

    return nullptr;
}

static void TriggerPulse(HudPulse& pulse)
{
    pulse.timer = pulse.duration;
}

static void UpdatePulse(HudPulse& pulse, float dt)
{
    if(pulse.timer > 0.0f)
    {
        pulse.timer -= dt;

        if(pulse.timer < 0.0f)
        {
            pulse.timer = 0.0f;
        }
    }
}

void HudAnimationSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();
    auto& hud = world.GetResource<HudAnimationResource>();
    auto& time = world.GetResource<TimeResource>();

    const ShotScore* score = GetCurrentShotScore(world);

    int chips = 0;
    int mult = 1;
    int shotScore = 0;

    if(score != nullptr)
    {
        chips = score->chips;
        mult = score->mult;
        shotScore = score->finalScore;
    }

    int previewScore = run.currentScore + shotScore;

    if(chips != hud.previousChips)
    {
        TriggerPulse(hud.chipsPulse);
        hud.previousChips = chips;
    }

    if(mult != hud.previousMult)
    {
        TriggerPulse(hud.multPulse);
        hud.previousMult = mult;
    }

    if(previewScore != hud.previousScore)
    {
        // TriggerPulse(hud.scorePulse);
        hud.previousScore = previewScore;
    }

    if(run.ballsRemaining != hud.previousBalls)
    {
        TriggerPulse(hud.ballsPulse);
        hud.previousBalls = run.ballsRemaining;
    }

    UpdatePulse(hud.chipsPulse, time.deltaTime);
    UpdatePulse(hud.multPulse, time.deltaTime);
    UpdatePulse(hud.scorePulse, time.deltaTime);
    UpdatePulse(hud.ballsPulse, time.deltaTime);
}
