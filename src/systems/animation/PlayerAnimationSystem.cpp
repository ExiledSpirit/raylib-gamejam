#include "PlayerAnimationSystem.hpp"

#include "../../components/animation/AnimationPlayer.hpp"
#include "../../utils/AnimationHelper.hpp"
#include "../../const/AnimationIds.hpp"
#include "../../resources/RunResource.hpp"

#include <ecs/components/Sprite.hpp>

void PlayerAnimationSystem(World& world)
{
    auto& assets =
        world.GetResource<AssetManager>();

    auto& run =
        world.GetResource<RunResource>();

    auto view =
        world.registry.view<
            AnimationPlayer,
            Sprite>();

    for(auto [entity, animation, sprite] : view.each())
    {
        (void)entity;

        sprite.flipX = false;

        std::string animationId =
            AnimationIds::PlayerIdle;

        switch(run.phase)
        {
            case RunPhase::WaitingToDropBall:
            {
                animationId = AnimationIds::PlayerIdle;
                break;
            }

            case RunPhase::BallFalling:
            {
                animationId = AnimationIds::PlayerIdle;
                // animationId = AnimationIds::PlayerReady;
                break;
            }

            case RunPhase::BallMissed: // Missed
            {
                animationId = AnimationIds::PlayerIdle;
            }

            case RunPhase::FirstStrikeAnimation: // Good or Great
            {
                animationId = AnimationIds::PlayerIdle;
                // animationId = AnimationIds::PlayerFirstStrike;
                break;
            }

            case RunPhase::SkillChecks: // Missed/ Great/ Good
            {
                animationId = AnimationIds::PlayerIdle;
                // animationId = AnimationIds::PlayerFirstStrike;
                break;
            }

            case RunPhase::LastStrikeAnimation: // Homerun
            {
                // animationId = AnimationIds::PlayerLastStrike;
                animationId = AnimationIds::PlayerIdle;
                break;
            }

            case RunPhase::BallRunning: // Multiplier
            {
                animationId = AnimationIds::PlayerIdle;
                break;
            }

            case RunPhase::ShotFinished: // Score counting
            {
                animationId = AnimationIds::PlayerIdle;
                break;
            }

            case RunPhase::MapWon: // Gold counting
            {
                animationId = AnimationIds::PlayerIdle;
                break;
            }

            case RunPhase::MapLost: // Slowed version of soundtrack
            {
                animationId = AnimationIds::PlayerIdle;
                break;
            }
        }

        PlayAnimation(
            animation,
            &assets.GetAnimation(animationId)
        );
    }
}