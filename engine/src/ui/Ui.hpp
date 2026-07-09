#pragma once

#include "../core/World.hpp"

#include <raylib.h>

void UiBeginFrame(World& world);
void UiEndFrame(World& world);

void UiPanel(Rectangle rect);
void UiLabel(Rectangle rect, const char* text, int fontSize, Color color);

bool UiButton(World& world, Rectangle rect, const char* text);

bool UiToggle(
    World& world,
    Rectangle rect,
    const char* label,
    bool value
);

int UiChoice(
    World& world,
    Rectangle rect,
    const char* label,
    int currentIndex,
    const char** options,
    int optionCount
);

float UiSlider(
    World& world,
    Rectangle rect,
    const char* label,
    float value,
    float step
);