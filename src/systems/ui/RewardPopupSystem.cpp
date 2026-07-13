#include "RewardPopupSystem.hpp"

#include "../../resources/RewardPopupResource.hpp"
#include "../../resources/EconomyResource.hpp"
#include "../../resources/CampaignResource.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"
#include "../../resources/ScreenTransitionResource.hpp"
#include "../../resources/GameScreenResource.hpp"

#include "../../utils/PhaseHelper.hpp"
#include "../../utils/ScreenTransitionHelper.hpp"
#include "../../utils/CampaignHelper.hpp"

#include <ecs/resources/TimeResource.hpp>
#include <input/InputResource.hpp>

static int MaxRevealChars(const RewardPopupLine& line)
{
    int labelSize =
        static_cast<int>(line.label.size());

    int dollarSize =
        line.gold;

    return labelSize > dollarSize
        ? labelSize
        : dollarSize;
}

void RewardPopupSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::LevelReward)
    {
        return;
    }

    auto& popup = world.GetResource<RewardPopupResource>();
    auto& time = world.GetResource<TimeResource>();
    auto& input = world.GetResource<InputResource>();
    auto& screenTransitionResource = world.GetResource<ScreenTransitionResource>();

    if(!popup.active)
    {
        return;
    }

    if(popup.currentLine < static_cast<int>(popup.lines.size()))
    {
        popup.charTimer += time.deltaTime;

        float secondsPerChar =
            1.0f / popup.charsPerSecond;

        while(popup.charTimer >= secondsPerChar)
        {
            popup.charTimer -= secondsPerChar;

            RewardPopupLine& line =
                popup.lines[popup.currentLine];

            line.visibleChars++;

            if(line.visibleChars >= MaxRevealChars(line))
            {
                line.visibleChars = MaxRevealChars(line);
                popup.currentLine++;
                break;
            }
        }

        return;
    }

    if(!popup.buttonVisible)
    {
        popup.buttonTimer += time.deltaTime;

        if(popup.buttonTimer >= popup.buttonDelay)
        {
            popup.buttonVisible = true;
        }

        return;
    }

    if(input.IsPressed("throw"))
    {
        auto& economy = world.GetResource<EconomyResource>();
        auto& campaign = world.GetResource<CampaignResource>();

        economy.gold += popup.totalGold;
        economy.powerGoldThisLevel = 0;

        popup.active = false;

        AdvanceCampaign(campaign);

        run.currentScore = 0;
        run.requiredScore = CalculateRequiredScore(campaign);
        resetLevelNumbers(world, run);

        // Later this can become RunPhase::Shop.
        SetRunPhase(run, RunPhase::Shop);
        RequestScreenTransition(screenTransitionResource, GameScreen::Shop, ScreenTransitionAction::EnterShop);
    }
}
