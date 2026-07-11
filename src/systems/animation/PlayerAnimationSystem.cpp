#include "PlayerAnimationSystem.hpp"

#include "../../components/animation/AnimationPlayer.hpp"
#include "../../utils/AnimationHelper.hpp"
#include "../../const/AnimationIds.hpp"
#include "../../resources/RunResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"

#include <ecs/components/Sprite.hpp>

#include <cmath>
#include <string>

static bool IsFacingRight(float facingRadians)
{
    return std::cos(facingRadians) > 0.0f;
}

static std::string GetPlayerAnimationId(
    RunPhase phase,
    bool facingRight
)
{
    switch(phase)
    {
        case RunPhase::WaitingToDropBall:
        case RunPhase::BallRunning:
        case RunPhase::ShotFinished:
        case RunPhase::MapWon:
        case RunPhase::MapLost:
        {
            return facingRight
                ? AnimationIds::PlayerIdleRight
                : AnimationIds::PlayerIdle;
            break;
        }

        case RunPhase::BallFalling:
        {
            return facingRight
                ? AnimationIds::PlayerReadyRight
                : AnimationIds::PlayerReady;
            break;
        }

        case RunPhase::BallMissed:
        {
            return facingRight
                ? AnimationIds::PlayerWhiffRight
                : AnimationIds::PlayerWhiff;
            break;
        }

        case RunPhase::FirstStrikeAnimation:
        case RunPhase::SkillChecks:
        {
            return facingRight
                ? AnimationIds::PlayerFirstStrikeRight
                : AnimationIds::PlayerFirstStrike;
            break;
        }

        case RunPhase::LastStrikeAnimation:
        {
            return facingRight
                ? AnimationIds::PlayerLastStrikeRight
                : AnimationIds::PlayerLastStrike;
            break;
        }
    }

    return facingRight
        ? AnimationIds::PlayerIdleRight
        : AnimationIds::PlayerIdle;
}

void PlayerAnimationSystem(World& world)
{
    auto& assets =
        world.GetResource<AssetManager>();

    auto& run =
        world.GetResource<RunResource>();

    auto& strike =
        world.GetResource<PlayerStrikeResource>();

    bool facingRight =
        IsFacingRight(strike.facingRadians);

    auto view =
        world.registry.view<
            AnimationPlayer,
            Sprite>();

    for(auto [entity, animation, sprite] : view.each())
    {
        (void)entity;

        // Since you now have mirrored sprites as separate animations,
        // keep flipX disabled.
        sprite.flipX = false;

        std::string animationId =
            GetPlayerAnimationId(
                run.phase,
                facingRight
            );

        PlayAnimation(
            animation,
            &assets.GetAnimation(animationId)
        );
    }
}