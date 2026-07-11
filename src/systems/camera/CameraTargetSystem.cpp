#include "CameraTargetSystem.hpp"

#include "../../resources/GameCameraResource.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"

#include <raylib.h>

struct SkillCheckCameraShakeSettings
{
    float intensity = 0.0f;
    float frequency = 48.0f;
    float maxOffset = 1.0f;
    float maxRotation = 0.04f;
};

static float GetAccumulatedLaunchPower(const PlayerStrikeResource& strike)
{
    return strike.basePower * strike.finalPowerMultiplier;
}

static SkillCheckCameraShakeSettings GetSkillCheckShakeSettings(
    const PlayerStrikeResource& strike
)
{
    float power = GetAccumulatedLaunchPower(strike);
    float basePower = strike.basePower;

    // No bonus or almost no bonus.
    if(power <= basePower * 1.05f)
    {
        return SkillCheckCameraShakeSettings{
            0.08f,  // intensity
            20.0f,  // frequency
            3.0f,   // maxOffset
            0.0f   // maxRotation
        };
    }

    // Small bonus.
    if(power <= basePower * 1.25f)
    {
        return SkillCheckCameraShakeSettings{
            0.14f,
            24.0f,
            4.f,
            0.0f
        };
    }

    // Medium bonus.
    if(power <= basePower * 1.50f)
    {
        return SkillCheckCameraShakeSettings{
            0.22f,
            30.0f,
            5.f,
            0.f
        };
    }

    // High bonus.
    if(power <= basePower * 1.80f)
    {
        return SkillCheckCameraShakeSettings{
            0.32f,
            62.0f,
            3.0f,
            0.16f
        };
    }

    // Very high bonus.
    return SkillCheckCameraShakeSettings{
        0.42f,
        68.0f,
        4.0f,
        0.22f
    };
}

void CameraTargetSystem(World& world)
{
    auto& camera = world.GetResource<GameCameraResource>();
    auto& run = world.GetResource<RunResource>();

    camera.target = camera.defaultTarget;
    camera.targetZoom = 1.0f;
    camera.targetSustainedShakeIntensity = 0.0f;

    if(
        run.phase == RunPhase::FirstStrikeAnimation ||
        run.phase == RunPhase::SkillChecks ||
        run.phase == RunPhase::LastStrikeAnimation ||
        run.phase == RunPhase::BallMissed
    )
    {
        auto& strike = world.GetResource<PlayerStrikeResource>();

        camera.target = Vector2{
            strike.playerPosition.x + 8.0f,
            strike.playerPosition.y - 18.0f
        };

        camera.targetZoom = 1.35f;
    }

    if(run.phase == RunPhase::SkillChecks)
    {
        auto& strike = world.GetResource<PlayerStrikeResource>();

        SkillCheckCameraShakeSettings shake =
            GetSkillCheckShakeSettings(strike);

        camera.targetZoom = 1.65f;

        camera.targetSustainedShakeIntensity = shake.intensity;
        camera.sustainedShakeFrequency = shake.frequency;
        camera.sustainedShakeMaxOffset = shake.maxOffset;
        camera.sustainedShakeMaxRotation = shake.maxRotation;
    }
}