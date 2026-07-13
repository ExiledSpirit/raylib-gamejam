#include "RunEndInputSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/ScreenTransitionResource.hpp"
#include "../../resources/SkillCheckResource.hpp"

#include "../../utils/SkillCheckUtils.hpp"
#include "../../utils/ScreenTransitionHelper.hpp"

#include <input/InputResource.hpp>

#include <box2d/box2d.h>

#include <vector>

void RunEndInputSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::MapLost)
    {
        return;
    }

    auto& input =
        world.GetResource<InputResource>();

    if(!input.IsPressed("throw"))
    {
        return;
    }

    auto& transition =
        world.GetResource<ScreenTransitionResource>();

    if(transition.active)
    {
        return;
    }

    RequestScreenTransition(
        transition,
        GameScreen::MainMenu,
        ScreenTransitionAction::ReturnToMenu
    );
}