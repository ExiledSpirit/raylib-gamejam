#pragma once

#include <core/World.hpp>
#include "../resources/MainMenuIntroResource.hpp"
#include "../const/AudioIds.hpp"
#include "AudioHelper.hpp"

#include <raylib.h>

#include <iomanip>
#include <sstream>
#include <string>

inline void LoadMainMenuIntroSpritesheet(World& world)
{
    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(intro.loaded)
    {
        return;
    }

    std::string path =
        std::string(ASSETS_PATH) + "/main_menu/intro_spritesheet.png";

    intro.spritesheet =
        LoadTexture(path.c_str());

    if(intro.spritesheet.id == 0)
    {
        TraceLog(
            LOG_WARNING,
            "MAIN MENU: Failed to load intro spritesheet: %s",
            path.c_str()
        );

        return;
    }

    SetTextureFilter(
        intro.spritesheet,
        TEXTURE_FILTER_POINT
    );

    intro.loaded = true;
}

inline void UnloadMainMenuIntroSpritesheet(World& world)
{
    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(intro.loaded && intro.spritesheet.id != 0)
    {
        UnloadTexture(intro.spritesheet);
    }

    intro.spritesheet = Texture2D{};
    intro.loaded = false;
}

inline void ResetMainMenuIntro(World& world)
{
    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    intro.active = true;
    intro.finished = false;

    intro.batSfxPlayed = false;
    intro.glassSfxPlayed = false;
    intro.musicStarted = false;

    intro.timer = 0.0f;
    intro.frameTimer = 0.0f;
    intro.currentFrame = 0;
}

inline void StartMainMenuSong(World& world)
{
    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(intro.musicStarted)
    {
        return;
    }

    intro.musicStarted = true;

    AudioHelper::StopMusic(AudioIds::StoreSoundTrack);

    AudioHelper::SetMusicPitchValue(
        AudioIds::MainSoundTrack,
        1.0f
    );

    AudioHelper::PlayMusic(
        AudioIds::MainSoundTrack,
        0.6f
    );
}

inline void FinishMainMenuIntro(World& world)
{
    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    intro.currentFrame =
        intro.frameCount - 1;

    intro.active = false;
    intro.finished = true;

    intro.timer =
        intro.startDelay;

    intro.frameTimer = 0.0f;

    StartMainMenuSong(world);
}