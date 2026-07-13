#include "ScreenTransitionSystem.hpp"

#include "../../resources/ScreenTransitionResource.hpp"
#include "../../resources/GameScreenResource.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"
#include "../../resources/ShopResource.hpp"
#include "../../resources/PowerUpDatabaseResource.hpp"

#include "../../utils/PhaseHelper.hpp"
#include "../../utils/ShopItemHelper.hpp"
#include "../../utils/SkillCheckUtils.hpp"

#include "../../utils/AudioHelper.hpp"
#include "../../const/AudioIds.hpp"

#include <ecs/resources/TimeResource.hpp>

static void ApplyTransitionAction(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();
    auto& transition = world.GetResource<ScreenTransitionResource>();
    auto& run = world.GetResource<RunResource>();

    screen.current = transition.targetScreen;

    switch(transition.action)
    {
        case ScreenTransitionAction::StartPlaying:
        {
            SetRunPhase(run, RunPhase::WaitingToDropBall);
            break;
        }

        case ScreenTransitionAction::EnterShop:
        {
            AudioHelper::PlaySfx(AudioIds::Bell, 0.18f);
            AudioHelper::PauseMusic(AudioIds::MainSoundTrack);
            AudioHelper::PlayMusic(AudioIds::StoreSoundTrack, 2.f);
            auto& screen = world.GetResource<GameScreenResource>();
            auto& skill = world.GetResource<SkillCheckResource>();
            auto& shop = world.GetResource<ShopResource>();
            auto& database = world.GetResource<PowerUpDatabaseResource>();

            screen.current = GameScreen::Shop;
            SetRunPhase(run, RunPhase::Shop);

            FillShopSlots(world);

            BeginSkillCheck(
                skill,
                SkillCheckContext::Shop,
                CreateShopSkillCheckTargets(shop, database),
                3.5f,
                0,
                1
            );

            break;
        }

        case ScreenTransitionAction::ExitShopToPlaying:
        {
            AudioHelper::StopMusic(AudioIds::StoreSoundTrack);
            AudioHelper::ResumeMusic(AudioIds::MainSoundTrack);
            SetRunPhase(run, RunPhase::WaitingToDropBall);
            break;
        }

        case ScreenTransitionAction::ReturnToMenu:
        {
            break;
        }

        default:
        {
            break;
        }
    }
}

void ScreenTransitionSystem(World& world)
{
    auto& transition = world.GetResource<ScreenTransitionResource>();

    if(!transition.active)
    {
        return;
    }

    auto& time = world.GetResource<TimeResource>();

    transition.timer += time.deltaTime;

    if(transition.phase == ScreenTransitionPhase::Covering)
    {
        if(transition.timer >= transition.coverDuration)
        {
            transition.timer = 0.0f;
            transition.phase = ScreenTransitionPhase::Uncovering;

            if(!transition.midpointApplied)
            {
                ApplyTransitionAction(world);
                transition.midpointApplied = true;
            }
        }

        return;
    }

    if(transition.phase == ScreenTransitionPhase::Uncovering)
    {
        if(transition.timer >= transition.uncoverDuration)
        {
            transition.active = false;
            transition.phase = ScreenTransitionPhase::None;
            transition.action = ScreenTransitionAction::None;
            transition.shapes.clear();
        }

        return;
    }
}