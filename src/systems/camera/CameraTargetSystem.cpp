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

    return SkillCheckCameraShakeSettings{
        0.15f, // intensity
        5.0f, // Frequency
        10.f + (strike.skillCheckCounter * 0.7f), // Max Offset
        0.25f // Max rotation
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