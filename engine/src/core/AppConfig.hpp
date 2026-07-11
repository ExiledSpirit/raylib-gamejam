#pragma once

#include <raylib.h>

struct AppConfig
{
    int windowWidth = 1600;
    int windowHeight = 900;

    int internalWidth = 512;
    int internalHeight = 288;

    const char* title = "Raylib Gamejam Engine";

    int targetFps = 60;
    int exitKey = KEY_APOSTROPHE;
};