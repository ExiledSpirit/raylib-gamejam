#pragma once

#include "../resources/CampaignResource.hpp"

#include <cmath>
#include <algorithm>

inline int RoundToNearest25(float value)
{
    return static_cast<int>(std::round(value / 25.0f)) * 25;
}

inline int GetLevelClearGold(const CampaignResource& campaign)
{
    switch(campaign.level)
    {
        case 1:
            return 3;

        case 2:
            return 5;

        case 3:
        default:
            return 8;
    }
}

inline int CalculateRequiredScore(const CampaignResource& campaign)
{
    // Level difficulty inside each act.
    // Level 3 is the "boss"/hard level.
    static constexpr float levelMultipliers[3] = {
        1.0f,  // Level 1
        1.8f,  // Level 2
        3.0f   // Level 3
    };

    constexpr float baseScore = 300.0f;

    // growth exp.
    constexpr float actGrowth = 3.f;

    int levelIndex =
        std::clamp(campaign.level - 1, 0, 2);

    float score =
        baseScore *
        levelMultipliers[levelIndex] *
        std::pow(actGrowth, static_cast<float>(campaign.act - 1));

    return RoundToNearest25(score);
}

inline void AdvanceCampaign(CampaignResource& campaign)
{
    campaign.level++;

    if(campaign.level > campaign.levelsPerAct)
    {
        campaign.level = 1;
        campaign.act++;
    }
}