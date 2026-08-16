#include "HudPayoutSystem.hpp"

#include "../../resources/HudAnimationResource.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/CampaignResource.hpp"
#include "../../utils/PhaseHelper.hpp"
#include "../../utils/LevelRewardUtils.hpp"

#include "../../const/AudioIds.hpp"
#include "../../utils/AudioHelper.hpp"

#include <ecs/resources/TimeResource.hpp>

#include <raymath.h>

#include <cmath>

static float EaseOutCubic(float t)
{
    float inv = 1.0f - t;
    return 1.0f - inv * inv * inv;
}

static void UpdatePulse(HudPulse& pulse, float dt)
{
    if(pulse.timer <= 0.0f)
    {
        return;
    }

    pulse.timer -= dt;

    if(pulse.timer < 0.0f)
    {
        pulse.timer = 0.0f;
    }
}

void HudPayoutSystem(World& world)
{
    auto& hud = world.GetResource<HudAnimationResource>();
    auto& run = world.GetResource<RunResource>();
    auto& time = world.GetResource<TimeResource>();
    auto& campaign = world.GetResource<CampaignResource>();

    float dt = time.deltaTime;

    hud.time += dt;

    UpdatePulse(hud.chipsPulse, dt);
    UpdatePulse(hud.multPulse, dt);
    UpdatePulse(hud.scorePulse, dt);
    UpdatePulse(hud.ballsPulse, dt);
    UpdatePulse(hud.payoutPulse, dt);

    if(hud.barShakeTimer > 0.0f)
    {
        hud.barShakeTimer -= dt;

        if(hud.barShakeTimer < 0.0f)
        {
            hud.barShakeTimer = 0.0f;
        }
    }

    if(!hud.payout.active)
    {
        return;
    }

    hud.payout.timer += dt;

    float t = hud.payout.timer / hud.payout.duration;

    if(t > 1.0f)
    {
        t = 1.0f;
    }

    float eased = EaseOutCubic(t);

    hud.payout.position = Vector2Lerp(
        hud.payout.startPosition,
        hud.payout.targetPosition,
        eased
    );

    if(t < 1.0f || hud.payout.applied)
    {
        return;
    }

    hud.payout.applied = true;
    hud.payout.active = false;

    run.currentScore += hud.payout.amount;

    hud.scorePulse.timer = hud.scorePulse.duration;
    hud.barShakeTimer = hud.barShakeDuration;

    bool reachedRequiredScore =
        run.currentScore >= run.requiredScore;

    AudioHelper::PlaySfx(AudioIds::Payout);

    if(reachedRequiredScore)
    {
        hud.barShakeStrength = 1.0f;

        // - win SFX
        // - background shader intensity
        // - small camera shake
        // - bar flash
        
        if (campaign.act == campaign.maxActs && campaign.level == campaign.levelsPerAct) {
            SetRunPhase(run, RunPhase::MapWon);
            return;
        }
        OpenLevelRewardPopup(world);
        SetRunPhase(run, RunPhase::LevelReward);
        return;
    }

    hud.barShakeStrength = 0.35f;

    if(run.ballsRemaining <= 0)
    {
        SetRunPhase(run, RunPhase::MapLost);
        return;
    }

    SetRunPhase(run, RunPhase::WaitingToDropBall);
}