#include "ShopSkillCheckResolverSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/SkillCheckResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"
#include "../../resources/PlayerPowerUpsResource.hpp"
#include "../../resources/GameScreenResource.hpp"
#include "../../resources/ShopResource.hpp"
#include "../../resources/PowerUpDatabaseResource.hpp"
#include "../../resources/EconomyResource.hpp"
#include "../../resources/ScreenTransitionResource.hpp"

#include "../../utils/PhaseHelper.hpp"
#include "../../utils/SkillCheckUtils.hpp"
#include "../../utils/ShopItemHelper.hpp"
#include "../../utils/ShopItemHelper.hpp"
#include "../../utils/PlayerStatsHelper.hpp"
#include "../../utils/PowerUpOwnershipHelper.hpp"
#include "../../utils/PlayerStatsHelper.hpp"

#include "../../utils/AudioHelper.hpp"
#include "../../utils/ShopFeedbackHelper.hpp"
#include "../../utils/ScreenTransitionHelper.hpp"
#include "../../const/AudioIds.hpp"
static Vector2 GetDeniedFeedbackPosition(
    const SkillCheckResult& result
)
{
    if(result.kind == SkillCheckTargetKind::Reroll)
    {
        return Vector2{320.0f, 88.0f};
    }

    if(result.kind == SkillCheckTargetKind::ShopItem)
    {
        if(result.itemIndex == 0)
        {
            return Vector2{150.0f, 162.0f};
        }

        if(result.itemIndex == 1)
        {
            return Vector2{490.0f, 162.0f};
        }
    }

    return Vector2{320.0f, 150.0f};
}
void ShopSkillCheckResolverSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::Shop)
    {
        return;
    }

    auto& skill =
        world.GetResource<SkillCheckResource>();

    if(!HasSkillCheckResult(skill))
    {
        return;
    }

    SkillCheckResult result =
        ConsumeSkillCheckResult(skill);

    if(result.context != SkillCheckContext::Shop)
    {
        return;
    }

    auto& shop =
        world.GetResource<ShopResource>();

    auto& database =
        world.GetResource<PowerUpDatabaseResource>();

    auto& economy =
        world.GetResource<EconomyResource>();

    auto& owned =
        world.GetResource<PlayerPowerUpsResource>();

    auto& screenTransitionResource =
        world.GetResource<ScreenTransitionResource>();

    switch(result.kind)
    {
        case SkillCheckTargetKind::ShopItem:
        {
            if(result.itemIndex < 0 ||
               result.itemIndex >= static_cast<int>(shop.slots.size()))
            {
                return;
            }

            ShopSlot& slot =
                shop.slots[result.itemIndex];

            const PowerUpDefinition* power =
                FindPowerUp(database, slot.powerUpId);

            if(power == nullptr)
            {
                return;
            }

            if(economy.gold < power->price)
            {
                TriggerShopDeniedFeedback(
                    world,
                    GetDeniedFeedbackPosition(result)
                );
                return;
            }

            economy.gold -= power->price;

            AddPowerUp(
                owned,
                power->id
            );

            RecalculatePlayerStats(world);

            AudioHelper::PlaySfx(AudioIds::ItemBuy);

            ReplaceShopSlot(
                world,
                result.itemIndex
            );

            // Important:
            // Do NOT call BeginSkillCheck here.
            // This updates the wheel targets while preserving the current needle.
            skill.targets =
                CreateShopSkillCheckTargets(
                    shop,
                    database
                );

            return;
        }

        case SkillCheckTargetKind::Reroll:
        {
            if(economy.gold < shop.rerollCost)
            {
                TriggerShopDeniedFeedback(
                    world,
                    GetDeniedFeedbackPosition(result)
                );
                return;
            }

            economy.gold -= shop.rerollCost;
            shop.rerollCost++;

            AudioHelper::PlaySfx(AudioIds::Reroll);

            FillShopSlots(world);

            // Important:
            // Do NOT call BeginSkillCheck.
            // Calling BeginSkillCheck resets the needle.
            skill.targets =
                CreateShopSkillCheckTargets(
                    shop,
                    database
                );

            return;
        }

        case SkillCheckTargetKind::Exit:
        {
            AudioHelper::PlaySfx(AudioIds::Bell, 0.18f);

            RequestScreenTransition(
                screenTransitionResource,
                GameScreen::Playing,
                ScreenTransitionAction::ExitShopToPlaying
            );

            EndSkillCheck(skill);

            shop.rerollCost = 1;
            SetRunPhase(
                run,
                RunPhase::WaitingToDropBall
            );

            return;
        }

        case SkillCheckTargetKind::Miss:
        default:
        {
            // In shop, missing should not exit.
            // It should just do nothing.
            return;
        }
    }
}