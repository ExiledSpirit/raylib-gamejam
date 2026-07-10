#include "StrikeCameraSystem.hpp"

#include "../../resources/GameCameraResource.hpp"
#include "../../resources/RunResource.hpp"

void StrikeCameraSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();
    auto& camera = world.GetResource<GameCameraResource>();

    switch(run.phase)
    {
        case RunPhase::FirstStrikeAnimation:
        case RunPhase::SkillChecks:
        case RunPhase::LastStrikeAnimation:
            camera.targetZoom = 1.35f;
            break;

        default:
            camera.targetZoom = 1.0f;
            break;
    }
}
