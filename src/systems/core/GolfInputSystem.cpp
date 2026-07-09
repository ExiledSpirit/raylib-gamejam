#include "GolfInputSystem.hpp"

#include <input/InputResource.hpp>
#include <ecs/resources/TimeResource.hpp>

#include "../../resources/LauncherResource.hpp"
#include "../../resources/RunResource.hpp"

#include <cmath>

void GolfInputSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::WaitingForShot)
    {
        return;
    }

    auto& input = world.GetResource<InputResource>();
    auto& time = world.GetResource<TimeResource>();
    auto& launcher = world.GetResource<LauncherResource>();

    if(input.IsPressed("throw"))
    {
        launcher.charging = true;
        launcher.power = 0.0f;
    }

    if(launcher.charging && input.IsDown("throw"))
    {
        launcher.aimAngle += launcher.aimSpeed * time.deltaTime;

        launcher.power += launcher.chargeSpeed * time.deltaTime;

        if(launcher.power > launcher.maxPower)
        {
            launcher.power = 0.0f;
        }
    }

    if(launcher.charging && input.IsReleased("throw"))
    {
        launcher.charging = false;

        // next step: spawn/launch Box2D ball here
        run.phase = RunPhase::BallRunning;
    }
}
