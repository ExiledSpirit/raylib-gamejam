#include "PlayingUiSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "GameHudSystem.hpp"
#include "SkillCheckUiSystem.hpp"
#include "../debugs/DebugUiSystem.hpp"
#include "RewardPopupRenderSystem.hpp"
#include "FloatingTextRenderSystem.hpp"

void PlayingUiSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Playing)
    {
        return;
    }

    GameHudSystem(world);
    SkillCheckUiSystem(world);
    FloatingTextRenderSystem(world);
    // DebugUiSystem(world);
    RewardPopupRenderSystem(world);
}