#include "MainMenuInputSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/MainMenuIntroResource.hpp"
#include "../../resources/ScreenTransitionResource.hpp"

#include "../../utils/MainMenuIntroHelper.hpp"
#include "../../utils/ScreenTransitionHelper.hpp"

#include <input/InputResource.hpp>

void MainMenuInputSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::MainMenu)
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

    auto& intro = world.GetResource<MainMenuIntroResource>();

    if(!intro.finished)
    {
        FinishMainMenuIntro(world);
        return;
    }

    RequestScreenTransition(
        transition,
        GameScreen::Playing,
        ScreenTransitionAction::StartPlaying
    );
}
