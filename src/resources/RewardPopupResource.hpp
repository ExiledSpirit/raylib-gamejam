#pragma once

#include <raylib.h>

#include <string>
#include <vector>

struct RewardPopupLine
{
    std::string label;
    int gold = 0;

    int visibleChars = 0;
};

struct RewardPopupResource
{
    bool active = false;
    bool buttonVisible = false;

    std::vector<RewardPopupLine> lines;

    int currentLine = 0;
    float charTimer = 0.0f;
    float charsPerSecond = 48.0f;

    float buttonTimer = 0.0f;
    float buttonDelay = 0.15f;

    int totalGold = 0;
};
