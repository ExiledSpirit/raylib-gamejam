#include "MainMenuSceneRenderSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/MainMenuIntroResource.hpp"

#include <raylib.h>

void MainMenuSceneRenderSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::MainMenu)
    {
        return;
    }

    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    ClearBackground(BLACK);

    if(!intro.loaded || intro.spritesheet.id == 0)
    {
        return;
    }

    int frameX =
        intro.currentFrame % intro.columns;

    int frameY =
        intro.currentFrame / intro.columns;

    Rectangle source{
        static_cast<float>(frameX * intro.frameWidth),
        static_cast<float>(frameY * intro.frameHeight),
        static_cast<float>(intro.frameWidth),
        static_cast<float>(intro.frameHeight)
    };

    Rectangle destination{
        0.0f,
        0.0f,
        640.0f,
        360.0f
    };

    DrawTexturePro(
        intro.spritesheet,
        source,
        destination,
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );
}