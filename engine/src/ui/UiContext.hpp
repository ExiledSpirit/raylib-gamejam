#pragma once

#include <raylib.h>

struct UiStyle
{
    Color panel = Color{10, 8, 24, 225};
    Color panelBorder = Color{80, 78, 140, 255};

    Color button = Color{24, 18, 52, 240};
    Color buttonFocused = Color{100, 82, 210, 255};
    Color buttonPressed = Color{135, 115, 255, 255};

    Color text = Color{235, 235, 255, 255};
    Color textMuted = Color{145, 145, 175, 255};

    Color selector = Color{255, 235, 130, 255};
};

struct UiContext
{
    UiStyle style{};

    Vector2 offset{0.0f, 0.0f};

    int focusedIndex = 0;
    int itemIndex = 0;
    int itemCount = 0;
    int previousItemCount = 0;

    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
    bool acceptPressed = false;
    bool cancelPressed = false;

    Vector2 selectorPosition{};
    Vector2 selectorTarget{};
    float selectorRotation = 0.f;
    bool selectorInitialized = false;
};