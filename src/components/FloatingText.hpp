#pragma once

#include <raylib.h>
#include <string>

struct FloatingText
{
    std::string text;

    Vector2 velocity{0.0f, -24.0f};

    float lifetime = 0.75f;
    float age = 0.0f;

    int fontSize = 10;
    Color color = WHITE;
};
