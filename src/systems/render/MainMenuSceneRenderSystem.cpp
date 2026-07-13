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

    ClearBackground(BLACK);

    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(!intro.loaded || intro.spritesheet.id == 0)
    {
        return;
    }

    int frameIndex =
        intro.currentFrame;

    if(frameIndex < 0)
    {
        frameIndex = 0;
    }

    if(frameIndex >= intro.frameCount)
    {
        frameIndex = intro.frameCount - 1;
    }

    Rectangle source{
        static_cast<float>(frameIndex * intro.frameWidth),
        0.0f,
        static_cast<float>(intro.frameWidth),
        static_cast<float>(intro.frameHeight)
    };

    Rectangle destination{
        0.0f,
        0.0f,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
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