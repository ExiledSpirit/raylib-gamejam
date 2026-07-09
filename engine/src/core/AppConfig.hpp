#pragma once

#include <raylib.h>

struct AppConfig
{
    int windowWidth = 1600;
    int windowHeight = 900;

    int internalWidth = 320;
    int internalHeight = 180;

    const char* title = "Raylib Gamejam Engine";

    int targetFps = 120;
    int exitKey = KEY_APOSTROPHE;
};