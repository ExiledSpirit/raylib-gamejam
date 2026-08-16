#pragma once

#include <raylib.h>

struct MainMenuIntroResource
{
    Texture2D spritesheet{};
    bool loaded = false;
    bool active = false;
    bool finished = false;

    bool batSfxPlayed = false;
    bool glassSfxPlayed = false;
    bool musicStarted = false;

    float startDelay = 1.5f;
    float timer = 0.0f;
    float frameTimer = 0.0f;
    float frameDuration = 1.0f / 24.0f;

    int currentFrame = 0;
    int frameCount = 43;

    int frameWidth = 640;
    int frameHeight = 360;

    int columns = 7;

    int glassFrame = 2;
    int musicFrame = 25;
};
