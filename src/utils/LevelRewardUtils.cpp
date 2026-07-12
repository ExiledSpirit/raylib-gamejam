#include "LevelRewardUtils.hpp"

#include "../resources/RewardPopupResource.hpp"
#include "../resources/RunResource.hpp"
#include "../resources/EconomyResource.hpp"

#include <algorithm>
#include <string>

static std::string RemainingBallsLabel(int balls)
{
    if(balls == 1)
    {
        return "1 remaining ball";
    }

    return std::to_string(balls) + " remaining balls";
}

void OpenLevelRewardPopup(World& world)
{
    auto& popup = world.GetResource<RewardPopupResource>();
    auto& run = world.GetResource<RunResource>();
    auto& economy = world.GetResource<EconomyResource>();

    popup.active = true;
    popup.buttonVisible = false;
    popup.lines.clear();

    popup.currentLine = 0;
    popup.charTimer = 0.0f;
    popup.buttonTimer = 0.0f;
    popup.totalGold = 0;

    int completionGold = 5;
    int remainingBallsGold = run.ballsRemaining;
    int powerGold = economy.powerGoldThisLevel;

    int interestGold =
        std::min(5, economy.gold / 5);

    popup.lines.push_back(
        RewardPopupLine{"Level complete", completionGold, 0}
    );

    if(remainingBallsGold > 0)
    {
        popup.lines.push_back(
            RewardPopupLine{RemainingBallsLabel(run.ballsRemaining), remainingBallsGold, 0}
        );
    }

    if(powerGold > 0)
    {
        popup.lines.push_back(
            RewardPopupLine{"Power bonus", powerGold, 0}
        );
    }

    if(interestGold > 0)
    {
        popup.lines.push_back(
            RewardPopupLine{"Interest", interestGold, 0}
        );
    }

    for(const RewardPopupLine& line : popup.lines)
    {
        popup.totalGold += line.gold;
    }
}
