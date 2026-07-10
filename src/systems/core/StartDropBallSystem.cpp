#include "StartDropBallSystem.hpp"

#include <input/InputResource.hpp>
#include "../../utils/PhaseHelper.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/IncomingBallResource.hpp"
#include "../../factories/IncomingBallFactory.hpp"

void StartDropBallSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::WaitingToDropBall)
    {
        return;
    }

    auto& input = world.GetResource<InputResource>();

    if(!input.IsPressed("throw"))
    {
        return;
    }

    CreateIncomingBall(world);

    SetRunPhase(run, RunPhase::BallFalling);
}