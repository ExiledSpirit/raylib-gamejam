#include "BallWallHitSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/ShotScore.hpp"
#include "../../components/Transform2D.hpp"

#include "../../resources/GameCameraResource.hpp"
#include "../../resources/TileMapResource.hpp"
#include "../../utils/CameraShakeUtils.hpp"

#include "../../factories/FloatingTextFactory.hpp"

#include "../../const/AudioIds.hpp"
#include "../../utils/AudioHelper.hpp"

#include <physics/PhysicsWorldResource.hpp>

#include <box2d/box2d.h>
#include <raylib.h>

static float Length(b2Vec2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

static int GetWallHitValue(float speedPixelsPerSecond)
{
    // 0..99   -> +1
    // 100..149 -> +2
    // 150..199 -> +3
    // etc.
    int value =
        static_cast<int>(speedPixelsPerSecond / 50.0f);

    return std::max(1, value);
}

static float GetWallHitVelocityRetention(float speedMetersPerSecond)
{
    constexpr float lowSpeed = 2.5f;
    constexpr float highSpeed = 10.0f;

    constexpr float lowSpeedRetention = 0.72f;
    constexpr float highSpeedRetention = 0.96f;

    float t =
        (speedMetersPerSecond - lowSpeed) /
        (highSpeed - lowSpeed);

    t =
        std::clamp(t, 0.0f, 1.0f);

    return lowSpeedRetention +
        t * (highSpeedRetention - lowSpeedRetention);
}

static bool SameBody(b2BodyId a, b2BodyId b)
{
    return B2_ID_EQUALS(a, b);
}

void BallWallHitSystem(World& world)
{
    auto& physicsWorld =
        world.GetResource<PhysicsWorldResource>();

    b2ContactEvents events =
        b2World_GetContactEvents(physicsWorld.worldId);

    auto view =
        world.registry.view<Ball, BallPhysicsBody, ShotScore, Transform2D>();
    auto& camera = world.GetResource<GameCameraResource>();

    for(int i = 0; i < events.hitCount; ++i)
    {
        const b2ContactHitEvent& hit =
            events.hitEvents[i];

        b2BodyId bodyA =
            b2Shape_GetBody(hit.shapeIdA);

        b2BodyId bodyB =
            b2Shape_GetBody(hit.shapeIdB);

        for(auto [entity, ball, physics, score, transform] : view.each())
        {
            (void)entity;
            (void)ball;

            bool ballWasInHit =
                SameBody(bodyA, physics.bodyId) ||
                SameBody(bodyB, physics.bodyId);

            if(!ballWasInHit)
            {
                continue;
            }
            b2Vec2 velocity =
                b2Body_GetLinearVelocity(physics.bodyId);

            float speedMeters =
                Length(velocity);

            float speedPixels =
                speedMeters * static_cast<float>(TILE_SIZE);

            int wallHitValue =
                GetWallHitValue(speedPixels);
            score.wallHits += wallHitValue;
            score.mult = 1 + score.wallHits;
            score.finalScore = score.chips * score.mult;

            // AudioHelper::PlaySfx(AudioIds::WallHit);
            AudioHelper::PlaySfx(AudioIds::Mult, 3.0f, 2.5f);

            if (speedMeters > 50) {
                AddCameraShake(
                    camera,
                    0.55f,  // intensity
                    0.12f,  // duration
                    10.0f,   // max offset
                    0.25f,  // max rotation
                    10.0f   // frequency
                );
            }

            CreateFloatingText(
                world,
                TextFormat("+%i mult", wallHitValue),
                Vector2{
                    transform.position.x + 8.0f,
                    transform.position.y - 18.0f
                },
                ORANGE
            );
        }
    }
}