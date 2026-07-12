#pragma once

#include <cmath>

struct CampaignResource
{
    int act = 1;
    int level = 1;

    int maxActs = 6;
    int levelsPerAct = 3;

    int globalLevelIndex = 0;
};

inline int RoundToNearest25(float value)
{
    return static_cast<int>(std::round(value / 25.0f)) * 25;
}

inline int CalculateRequiredScore(int globalLevelIndex)
{
    constexpr float baseScore = 250.0f;
    constexpr float growth = 1.3f;

    return RoundToNearest25(
        baseScore * std::pow(growth, static_cast<float>(globalLevelIndex))
    );
}

inline void AdvanceCampaign(CampaignResource& campaign)
{
    campaign.globalLevelIndex++;

    int localIndex =
        campaign.globalLevelIndex %
        (campaign.maxActs * campaign.levelsPerAct);

    campaign.act =
        localIndex / campaign.levelsPerAct + 1;

    campaign.level =
        localIndex % campaign.levelsPerAct + 1;
}
