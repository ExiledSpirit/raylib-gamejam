#pragma once

struct EconomyResource
{
    int gold = 5;

    // Power effects can increase this during a level.
    int powerGoldThisLevel = 0;
};
