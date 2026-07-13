#include "MainMenuIntroSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/MainMenuIntroResource.hpp"

#include "../../utils/AudioHelper.hpp"
#include "../../utils/MainMenuIntroHelper.hpp"
#include "../../const/AudioIds.hpp"

#include <ecs/resources/TimeResource.hpp>

void MainMenuIntroSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::MainMenu)
    {
        return;
    }

    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(!intro.active)
    {
        return;
    }

    auto& time =
        world.GetResource<TimeResource>();

    float dt =
        time.deltaTime;

    if(!intro.batSfxPlayed)
    {
        intro.batSfxPlayed = true;

        AudioHelper::PlaySfx(
            AudioIds::MainMenuBatStrike,
            0.6f
        );
    }

    intro.timer += dt;

    if(intro.timer < intro.startDelay)
    {
        return;
    }

    if(!intro.loaded || intro.spritesheet.id == 0)
    {
        intro.finished = true;
        intro.active = false;
        return;
    }

    intro.frameTimer += dt;

    while(intro.frameTimer >= intro.frameDuration)
    {
        intro.frameTimer -= intro.frameDuration;

        if(intro.currentFrame < intro.frameCount - 1)
        {
            intro.currentFrame++;
        }
        else
        {
            intro.finished = true;
            intro.active = false;
            return;
        }

        int frameNumber =
            intro.currentFrame + 1;

        if(frameNumber >= intro.glassFrame &&
           !intro.glassSfxPlayed)
        {
            intro.glassSfxPlayed = true;

            AudioHelper::PlaySfx(
                AudioIds::GlassBreak,
                0.5f
            );
        }

        if(frameNumber >= intro.musicFrame)
        {
            StartMainMenuSong(world);
        }
    }
}