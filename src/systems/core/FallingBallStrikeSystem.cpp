#include "FallingBallStrikeSystem.hpp"

#include <input/InputResource.hpp>
#include <ecs/resources/TimeResource.hpp>

#include "../../components/IncomingBall.hpp"
#include "../../components/Transform2D.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"
#include "../../resources/PlayerStatsResource.hpp"
#include "../../utils/AudioHelper.hpp"

#include "../../utils/PhaseHelper.hpp"
#include "../../factories/FloatingTextFactory.hpp"

#include "../../const/AudioIds.hpp"
#include "../../utils/AudioHelper.hpp"

#include <raylib.h>

static StrikeQuality GetStrikeQuality(
    Vector2 ballPosition,
    float radius,
    const PlayerStrikeResource& strike
)
{
    if(CheckCollisionCircleRec(ballPosition, radius, strike.perfectZone))
    {
        return StrikeQuality::Perfect;
    }

    if(CheckCollisionCircleRec(ballPosition, radius, strike.topZone))
    {
        return StrikeQuality::Good;
    }

    if(CheckCollisionCircleRec(ballPosition, radius, strike.bottomZone))
    {
        return StrikeQuality::Good;
    }

    return StrikeQuality::None;
}

static void LoseStrike(World& world, entt::entity incomingEntity)
{
    auto& run = world.GetResource<RunResource>();
    auto& striker = world.GetResource<PlayerStrikeResource>();

    run.ballsRemaining--;

    world.registry.destroy(incomingEntity);

    SetRunPhase(run, RunPhase::BallMissed);
    CreateFloatingText(
        world,
        "MISS",
        Vector2{
            striker.playerPosition.x + 8.0f,
            striker.playerPosition.y - 18.0f
        },
        GRAY,
        1.5f
    );
    
    AudioHelper::PlaySfx(AudioIds::Whiff, 1.0f, 1.0f);
}

void FallingBallStrikeSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallFalling)
    {
        return;
    }

    auto& time = world.GetResource<TimeResource>();
    auto& input = world.GetResource<InputResource>();
    auto& strike = world.GetResource<PlayerStrikeResource>();
    auto& stats = world.GetResource<PlayerStatsResource>();

    auto view = world.registry.view<IncomingBall, Transform2D>();

    for(auto [entity, incoming, transform] : view.each())
    {
        transform.position.x += incoming.velocity.x * time.deltaTime;
        transform.position.y += incoming.velocity.y * time.deltaTime;

        bool touchedGround =
            transform.position.y + incoming.radius >= incoming.groundY;

        if(touchedGround)
        {
            LoseStrike(world, entity);
            return;
        }

        if(incoming.ignoreInputThisFrame)
        {
            incoming.ignoreInputThisFrame = false;
            return;
        }

        if(input.IsPressed("throw"))
        {
            StrikeQuality quality = GetStrikeQuality(
                transform.position,
                incoming.radius,
                strike
            );

            if(quality == StrikeQuality::None)
            {
                LoseStrike(world, entity);
                return;
            }

            strike.firstStrikeQuality = quality;
            strike.firstStrikeTimer = 0.0f;

            strike.basePower = stats.basePower;

            if(quality == StrikeQuality::Perfect)
            {
                CreateFloatingText(
                    world,
                    "PERFECT!!",
                    Vector2{
                        strike.playerPosition.x + 8.0f,
                        strike.playerPosition.y - 18.0f
                    },
                    GOLD,
                    1.5f,
                    16.f
                );

                AudioHelper::PlaySfx(AudioIds::FirstStrikePerfect, 0.3f, 1.f);

                strike.finalPowerMultiplier =
                    stats.perfectFirstStrikeMultiplier;
            }
            else
            {
                CreateFloatingText(
                    world,
                    "Good!",
                    Vector2{
                        strike.playerPosition.x + 8.0f,
                        strike.playerPosition.y - 18.0f
                    },
                    GOLD,
                    1.5f,
                    16.f
                );
                strike.finalPowerMultiplier =
                    stats.goodFirstStrikeMultiplier;
            }

            // Store the contact/ball position for the later real physics launch.
            strike.struckBallPosition = transform.position;

            world.registry.destroy(entity);

            SetRunPhase(run, RunPhase::FirstStrikeAnimation);
            AudioHelper::PlaySfx(AudioIds::LastStrike, 0.3f, 0.5f);

            return;
        }

        return;
    }
}