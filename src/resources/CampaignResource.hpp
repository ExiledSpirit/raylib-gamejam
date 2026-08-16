#pragma once

#include <cmath>

struct CampaignResource
{
    int act = 1;
    int level = 1;

    int maxActs = 3;
    int levelsPerAct = 3;

    __int128_t maximumScore = 0;
};
