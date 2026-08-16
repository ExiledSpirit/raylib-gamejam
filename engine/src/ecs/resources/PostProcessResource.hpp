#pragma once

#include <raylib.h>

struct PostProcessResource
{
    Shader shader{};
    bool loaded = false;
    bool enabled = true;
};
