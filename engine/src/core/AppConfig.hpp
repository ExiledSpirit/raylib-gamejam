#pragma once

#include <raylib.h>

struct AppConfig
{
    int windowWidth = 1600;
    int windowHeight = 900;

    int internalWidth = 640;
    int internalHeight = 360;

    const char* title = "TOY OUT";

    int targetFps = 120;
    int exitKey = KEY_APOSTROPHE;

    Font fontFamily;
};