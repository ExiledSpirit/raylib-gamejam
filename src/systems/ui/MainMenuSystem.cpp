#include <ui/UiContext.hpp>
#include <ui/Ui.hpp>
#include "MainMenuSystem.hpp"
#include "../../resources/GameScreenResource.hpp"

void MainMenuUiSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();
    auto& ui = world.GetResource<UiContext>();

    if(screen.screen != GameScreen::Menu)
    {
        return;
    }

    ui.offset = Vector2{
        0,
        0
    };

    UiBeginFrame(world);

    constexpr float MAIN_Y = 0.0f;

    if(screen.menuPanel == MenuPanel::Main)
    {
        if(UiButton(world, Rectangle{110.0f, MAIN_Y + 82.0f, 100.0f, 16.0f}, "PLAY"))
        {
            screen.screen = GameScreen::Playing;
        }

        if(UiButton(world, Rectangle{110.0f, MAIN_Y + 104.0f, 100.0f, 16.0f}, "LOAD GAME"))
        {
            screen.menuPanel = MenuPanel::LoadGame;
        }

        if(UiButton(world, Rectangle{110.0f, MAIN_Y + 126.0f, 100.0f, 16.0f}, "OPTIONS"))
        {
            screen.menuPanel = MenuPanel::Options;
        }

        if(UiButton(world, Rectangle{110.0f, MAIN_Y + 148.0f, 100.0f, 16.0f}, "QUIT"))
        {
            CloseWindow();
        }
    }

    UiEndFrame(world);
}
